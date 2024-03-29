
/*
Copyright (c) 1995,1996 The Regents of the University of California.
All rights reserved.

Permission to use, copy, modify, and distribute this software for any
purpose, without fee, and without written agreement is hereby granted,
provided that the above copyright notice and the following two
paragraphs appear in all copies of this software.

IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

Copyright 2017-2019 Michael Linderman.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */

#include <algorithm>
#include <cstdlib>
#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

#include "ast.h"
#include "semant.h"
#include "utilities.h"

namespace cool {

// clang-format off
/**
   * @name Predefined symbols used in Cool
   *
   * extern indicates that these variables are defined elsewhere (in this case ast_consumer.cc)
   * and so C++ doesn't need to create any storage.
   *
   * @{
   */
extern Symbol
    *arg,
    *arg2,
    *Bool,
    *concat,
    *cool_abort,
    *copy,
    *Int,
    *in_int,
    *in_string,
    *IO,
    *isProto,
    *length,
    *Main,
    *main_meth,
    *No_class,
    *No_type,
    *Object,
    *out_int,
    *out_string,
    *prim_slot,
    *self,
    *SELF_TYPE,
    *String,
    *str_field,
    *substr,
    *type_name,
    *val;
//@}
// clang-format on

Symbol *leaf;
// such that LUB(leaf, x) = x, LUB(x, leaf) = x, LUB(leaf, leaf) = leaf
// leaf <= any type

std::ostream& SemantError::operator()(const SemantNode* node) { return (*this)(node->klass()); }


// Contructor of SemantKlassTable
// Store all the class names that have appeared
SemantKlassTable::SemantKlassTable(SemantError& error, Klasses* klasses)
    : KlassTable(), error_(error) {

    // Pass 1, Part 1: Add classes into SemantKlassTable
    for (auto klass : *klasses) {
        // std::cerr << "name:" << klass->name() <<
        //              ", parent: " << klass->parent() << std::endl;

        // Check whether a class is already defined
        SemantNode * old_node = ClassFind(klass->name());
        if (old_node) {
            error_(klass) << "Class " << klass->name() << " redefined." << std::endl;
            continue;
        }
        // If no error, then we install that class in our SemantKlassTable
        InstallClass(klass, true /*Can Inherit*/, false /*NotBasic*/);
    }

    // Pass 1, Part 2: Create inheritance graph and check for cycles
    for (auto node : nodes_) {
        // Create Inheritance graph
        SemantNode *parent_node = ClassFind(node->parent_name());
        if (!parent_node) {
            error_(node) << "Parent class " << node->parent_name() << " is not defined" << std::endl;
            continue;
        }
        if (!parent_node->inheritable()) {
            error_(node) << "Can't inherit from " << node->parent_name() << " class" << std::endl;
            continue;
        }

        node->parent_ = parent_node;  // Link from child to parent
        parent_node->children_.push_back(node);
    }

    if (error_.errors() > 0) return;  // Can't continue with class table construction if errors found

    // Check for cycles
    traverse(root());
    for (auto node : nodes_) {
        if (node->track_visit_ == UNVISITED) {
            error_(node) << "Cyclical inheritance detected" << std::endl;
        }
    }
    if (error_.errors() > 0) return;  // Can't continue with class table construction if errors found

} // end SemantKlassTable constructor


void Semant(Program* program) {

    // Initialize error tracker (and reporter)
    SemantError error(std::cerr);

    // Perform semantic analysis...
    // Constructor of a semant class table.
    // Inheritance graph is created along the way.
    SemantKlassTable klass_table(error, program->klasses());

    // Halt program with non-zero exit if there are semantic errors
    if (error.errors()) { // If number of errors reported is non-zero
        std::cerr << "Compilation halted due to static semantic errors." << std::endl;
        exit(1);
    }

    // Create scoped table for each class containing attr names and method names
    klass_table.make_all_sctables(klass_table.root());

    if (error.errors()) { // If number of errors reported is non-zero
        std::cerr << "Compilation halted due to static semantic errors." << std::endl;
        exit(1);
    }

    klass_table.Typecheck_all();

    if (error.errors()) { // If number of errors reported is non-zero
        std::cerr << "Compilation halted due to static semantic errors." << std::endl;
        exit(1);
    }

} // end void Semant(Program* program)




/*
 **********************************************************************
 * Below are all the helper and additional functions declared in semant.h
 **********************************************************************
 */


/*
 * Part I: Check the inheritance graph is sound
 */

// Traverse an inheritance graph in depth-first order to check for cycles
void SemantKlassTable::traverse(SemantNode *klass_node) {

    // check if a klass_node is unvisited, being visited, or already visited
    if (klass_node->track_visit_) { // if either being visited or already visited
        error_(klass_node) << "Cycle pointing to class " << klass_node->name()
                           << " is detected.";
        return;
    }

    klass_node->track_visit_ = VISITING;

    // recursively call traverse() on each child node
    for (auto child : klass_node->children_) {
        traverse(child);
    }

    klass_node->track_visit_ = VISITED;
} // end void traverse(SemantNode *klass_node)



/*
 * Part II: Create scoped tables
 */

// Create method-tables for all SemantNode
// Not sure whether any error will be detected here
void SemantKlassTable::make_all_sctables(SemantNode *klass_node) {

    // duplicate parent class' scoped-tables (both M-table and O-table)
    klass_node->mtable_ = klass_node->parent()->mtable_;
    klass_node->otable_ = klass_node->parent()->otable_;

    auto &mtable = klass_node->mtable_; // method-table of current klass_node
    auto &otable = klass_node->otable_; // object-table of current klass_node

    // Push a new scope onto scopestack
    mtable.EnterScope();
    otable.EnterScope();

    for (auto feature : *klass_node->klass()->features()) {
        if (feature->attr()) { // if the feature is an attribute
            if (otable.Lookup(feature->name()))
            // if the attr is already defined in some ancestor klass
            {
                error_(klass_node) << otable << std::endl;
                error_(klass_node) << "Attribute " << feature->name()
                    << " is redefined in class " << klass_node->name() << std::endl;
            } else // if the attr is never defined before
            {
                otable.AddToScope(feature->name(), feature->decl_type());
            }

        } else { // if the feature is a method

            Method *method_info = (Method *)feature; // Method is inhertied from Feature
            Method *found_method = mtable.Lookup(method_info->name());

            if (found_method)
            // if the method is already defined in some ancestor klass
            {
                // Need to make sure that the method name, the return type, and all formal names match in two methods

                const Formals *formals_now = method_info->formals();
                const Formals *formals_before = found_method->formals();
                bool error_flag = false;

                // Compare the return type
                if (found_method->decl_type() != method_info->decl_type())
                // if the return types of methodes don't match
                {
                    error_(klass_node) << "Method " << klass_node->name() << "."
                        << method_info->name() << " should have returned type \""
                        << found_method->decl_type()
                        << "\" but type \"" << method_info->decl_type()
                        << "\" is returned.\n";
                    error_flag = true;
                    continue;
                }

                // Compare the size of formal lists
                if (formals_now->size() != formals_before->size())
                // if the size of formal lists don't match
                {
                    error_(klass_node) << "Method " << klass_node->name() << "."
                        << method_info->name() << " should have had "
                        << formals_before->size()
                        << " formals but currently have " << formals_now->size()
                        << " formals.\n";
                    error_flag = true;
                    continue;
                }

                auto formal_now = formals_now->begin();
                auto formal_now_end = formals_now->end();
                auto formal_before = formals_before->begin();
                auto formal_before_end = formals_before->end();

                // Check whether each pair of formals have the same type
                while (formal_now != formal_now_end
                        && formal_before != formal_before_end)
                {
                    Symbol *type_now = (*formal_now)->decl_type();
                    Symbol *type_before = (*formal_before)->decl_type();
                    if (type_now != type_before) {
                        error_(klass_node) << "The argument \"" << (*formal_now)->name()
                            << "\" of method " << klass_node->name() << "."
                            << method_info->name() << "() should have had type \""
                            << type_before << "\" but currently has type \"" <<
                            type_now << "\"\n";
                        error_flag = true;
                    }

                    formal_now++;
                    formal_before++;
                }

                if (!error_flag) {
                    mtable.AddToScope(method_info->name(), method_info);
                }
            } // end if the method is already defined in some ancestor klass
            else // if the method is never defined before
            {
                mtable.AddToScope(method_info->name(), method_info);
            } // end else
        } // end else
    } // end for

    // recursively make_all_sctables on all children klasses
    for (auto child : klass_node->children_) {
        make_all_sctables(child);
    }

} // end void make_all_sctables(SemantNode *klass_node)



/*
 * Part III: Helper functions related to of Semantic Environment
 */

// Constructor of semantic environment
SemantEnv::SemantEnv(SemantKlassTable *klass_table_arg,
           SemantNode *curr_semant_node_arg,
           SemantError &error_env_arg) :
           klass_table(klass_table_arg),
           curr_semant_node(curr_semant_node_arg),
           error_env(error_env_arg) {}

void SemantKlassTable::Typecheck_all() {
    Typecheck_subgraph(root());

    // Check whethe Main and main are present
    SemantNode *Main_node = ClassFind(Main);
    if (!Main_node) {error_() << "Class Main is not defined\n"; return; }
    if (!Main_node->mtable_.Lookup(main_meth)) {error_() << "Method main is not defined\n"; return;}
}

// Type check all the classes in the subgraph of the inheritance graph
// where the root of subgraph is klass_node
void SemantKlassTable::Typecheck_subgraph(SemantNode *klass_node) {
    // Construct the semantic environment specific to klass_node
    SemantEnv envnow(this, klass_node, error_);

    // Traverse the AST under klass_node and do Typechecking
    klass_node->klass()->Typecheck(envnow);

    for (auto child : klass_node->children_) {
        Typecheck_subgraph(child);
    }
}

// Check whether type1 <= type2
bool SemantEnv::type_LE(Symbol *type1, Symbol *type2) {
    if (type1 == leaf) {return true; }
    if (type2 == leaf && type1 != leaf) {return false; }

    if (type1 != SELF_TYPE && type2 != SELF_TYPE)
    // When the comparison between types does not involve SELF_TYPE
    {
        SemantNode *klass_node_1 = klass_table->ClassFind(type1);
        SemantNode *klass_node_2 = klass_table->ClassFind(type2);
        return klass_table->SNLE(klass_node_1, klass_node_2);
    }
    // Below are the extensions of <= operator between types to SELF_TYPE
    else if (type1 == SELF_TYPE && type2 == SELF_TYPE) {return true; }
    else if (type1 != SELF_TYPE && type2 == SELF_TYPE) {return false; }
    else if (type1 == SELF_TYPE && type2 != SELF_TYPE) {
        return klass_table->SNLE(curr_semant_node, klass_table->ClassFind(type2));
    }
} // end SemantEnv::type_LE(Symbol *type1, Symbol *type2)

// Check whether the first SemantNode is the descendant of or the same as the second SemantNode
bool SemantKlassTable::SNLE(SemantNode *klass_node_1, SemantNode *klass_node_2) {
    if (klass_node_1 == klass_node_2) {return true; }

    for (auto child : klass_node_2->children_) {
        if (SNLE(klass_node_1, child)) {return true;}
    }

    return false;
}

// Find the least upper bound of two types
Symbol *SemantEnv::type_LUB(Symbol *type1, Symbol *type2) {
    if (type1 == leaf) {return type2; }
    if (type2 == leaf) {return type1; }

    SemantNode *klass_node_1, *klass_node_2;

    // Need to extend the LUB operation to SELF_TYPE
    if (type1 == SELF_TYPE && type2 == SELF_TYPE) {return SELF_TYPE; }

    else if (type1 == SELF_TYPE && type2 != SELF_TYPE) {
        klass_node_1 = curr_semant_node;
        klass_node_2 = klass_table->ClassFind(type2);
    }

    else if (type1 != SELF_TYPE && type2 == SELF_TYPE) {
        klass_node_1 = klass_table->ClassFind(type1);
        klass_node_2 = curr_semant_node;
    }

    else {
        klass_node_1 = klass_table->ClassFind(type1);
        klass_node_2 = klass_table->ClassFind(type2);
    }

    SemantNode *lowest_ances_node = klass_table->SNLUB(klass_node_1, klass_node_2);

    if (lowest_ances_node) {
        return lowest_ances_node->name();
    } else {
        return Object;
    }
} // end Symbol *SemantEnv::type_LUB(Symbol *type1, Symbol *type2)

// Find the lowest common ancestor of two SemandNode's
// If they don't share a common ancestor, return null
SemantNode *SemantKlassTable::SNLUB(SemantNode *klass_node_1, SemantNode *klass_node_2) {
    if (klass_node_1 == klass_node_2) {return klass_node_1; }
    SemantNode *next_up = klass_node_2->parent();
    if (next_up == NULL) {return NULL; }
    if (SNLE(klass_node_1, next_up)) {return next_up; }
    return SNLUB(klass_node_1, next_up);
}



/*
 * Part IV: Type checking
 */

void Klass::Typecheck(SemantEnv &env) {
    for (auto feature : *features()) {
        feature->Typecheck(env);
    }
}

void Feature::Typecheck(SemantEnv &env) {
    if (attr())
    // If the feature is an attribute
    {
        Attr *attr = (Attr *)this;
        Expression *expr = attr->init();
        env.curr_semant_node->otable_.EnterScope();
        env.curr_semant_node->otable_.AddToScope(self, SELF_TYPE);
        expr->Typecheck(env);
        env.curr_semant_node->otable_.ExitScope();

        // catch error if the declared type of attribute does not exist
        if (!env.klass_table->ClassFind(attr->decl_type())) {
            env.error_env(env.curr_semant_node->klass(), this) << "Type \"" << attr->decl_type() << "\" is undefined\n";
            return;
        }

        // case for [Attr-No-Init]
        if (expr->type() == No_type) {return; }

        // catch error for type inconsistency for [Attr-Init]
        if (!env.type_LE(expr->type(), decl_type())) {
            env.error_env(env.curr_semant_node->klass(), this) << "Inconsistent types in attribute initializer: attrbute \"" << attr->name() << "\" has type \"" << decl_type() << "\" but it is assigned an expression of type \"" << expr->type() << "\"\n";
        }
    } // end if the feature is an attribute
    else
    // If the feature is a method
    {
        Method *meth = (Method *)this;
        env.curr_semant_node->otable_.EnterScope();
        env.curr_semant_node->otable_.AddToScope(self, SELF_TYPE);

        for (auto formal : *meth->formals()) {
            // Check repeating formal name
            if (env.curr_semant_node->otable_.Probe(formal->name())) {
                env.error_env(env.curr_semant_node->klass(), this) << "Formal name \"" << formal->name() << "\" is already defined\n";
                continue;
            }

            if (!env.klass_table->ClassFind(formal->decl_type()))
            // if the type of a formal is undefined
            {
                env.error_env(env.curr_semant_node->klass(), this) << "Type \"" << formal->decl_type() << "\" is undefined\n";
                env.curr_semant_node->otable_.AddToScope(formal->name(), Object);
            }

            else if (formal->decl_type() == SELF_TYPE)
            // if the type of a formal is SELF_TYPE
            {
                env.error_env(env.curr_semant_node->klass(), this) << "Formals cannot have type \"SELF_TYPE\"\n";
                env.curr_semant_node->otable_.AddToScope(formal->name(), Object);
            }

            else {
                env.curr_semant_node->otable_.AddToScope(formal->name(), formal->decl_type());
            }
        } // end for

        meth->body_->Typecheck(env);
        env.curr_semant_node->otable_.ExitScope();

        // catch error if the declared type of method does not exist
        if (!env.klass_table->ClassFind(meth->decl_type())) {
            env.error_env(env.curr_semant_node->klass(), this) << "Type \"" << meth->decl_type() << "\" is undefined\n";
            return;
        }

        // Waive for <basic class>
        if (meth->body_->type() == No_type) {return; }

        // catch error for type inconsistency for [Attr-Init]
        if (!env.type_LE(meth->body_->type(), decl_type())) {
            env.error_env(env.curr_semant_node->klass(), this) << "Inconsistent types in method definition: method \"" << meth->name() << "\" has type \"" << decl_type() << "\" but it is assigned an expression of type \"" << meth->body_->type() << "\"\n";
        }

    } // end else the feature is a method
} // end void Feature::Typecheck(SemantEnv &env)

void BoolLiteral::Typecheck(SemantEnv &env) {
    set_type(Bool);
}

void IntLiteral::Typecheck(SemantEnv &env) {
    set_type(Int);
}

void StringLiteral::Typecheck(SemantEnv &env) {
    set_type(String);
}

void Ref::Typecheck(SemantEnv &env) {
    Symbol *type = env.curr_semant_node->otable_.Lookup(name_);
    // Need to check whether the objectID is undefined
    if (type) {set_type(type); }
    else {
        env.error_env(env.curr_semant_node->klass(), this) << "ObjectID \"" << name_ << "\" is undefined\n";
        set_type(Object);
    }

}

void Assign::Typecheck(SemantEnv &env) {
    Symbol *type_lhs = env.curr_semant_node->otable_.Lookup(name_);
    value_->Typecheck(env);
    Symbol *type_rhs = value_->type();

    if (env.type_LE(type_rhs, type_lhs)) {
        set_type(type_rhs);
    } else {
        env.error_env(env.curr_semant_node->klass(), this) << "Inconsistent types in assignment: Assign a value of type \"" << type_rhs << "\" to an objectID of type \"" << type_lhs << "\"\n";
    }
} // end void Assign::Typecheck(SemantEnv &env)

void Knew::Typecheck(SemantEnv &env) {
    if (name_ == SELF_TYPE) {
        set_type(SELF_TYPE);
    } else {
        // for expression "new XXX"
        // We need to check whether class XXX is defined in the first place
        if (env.klass_table->ClassFind(name_)) {set_type(name_); }
        else {
            env.error_env(env.curr_semant_node->klass(), this) << "Type \"" << name_ << "\" is undefined.\n";
            set_type(Object);
        }
    }
} // end void Knew::Typecheck(SemantEnv &env)

void Cond::Typecheck(SemantEnv &env) {
    pred_->Typecheck(env);
    then_branch_->Typecheck(env);
    else_branch_->Typecheck(env);

    if (pred_->type() != Bool) {
        env.error_env(env.curr_semant_node->klass(), this) << "Predicate should evaluate to type \"Bool\", but it has type \"" << pred_->type() << "\" instead\n";
        set_type(Object);
        return;
    }

    set_type(env.type_LUB(then_branch_->type(), else_branch_->type()));
} // end void Cond::Typecheck(SemantEnv &env)

void Block::Typecheck(SemantEnv &env) {
    // The parsing rules already ensured that there are more than one expression in a block

    for (auto expr : *body_) {
        expr->Typecheck(env);
        set_type(expr->type());
    }
} // end void Block::Typecheck(SemantEnv &env)

void Loop::Typecheck(SemantEnv &env) {
    pred_->Typecheck(env);
    body_->Typecheck(env);
    set_type(Object);

    if (pred_->type() != Bool) {
        env.error_env(env.curr_semant_node->klass(), this) << "Predicate should evaluate to type \"Bool\", but it has type \"" << pred_->type() << "\" instead\n";
    }
} // end void Loop::Typecheck(SemantEnv &env)

void Let::Typecheck(SemantEnv &env) {
    init_->Typecheck(env);
    bool error_flag = false;
    Symbol *decl_type_final;
    // Finalize declare type
    if (decl_type_ == SELF_TYPE) {
        decl_type_final = SELF_TYPE;
    } else {
        // for expression "new XXX"
        // We need to check whether class XXX is defined in the first place
        if (env.klass_table->ClassFind(decl_type_)) {decl_type_final = decl_type_; }
        else {
            env.error_env(env.curr_semant_node->klass(), this) << "Type \"" << decl_type_ << "\" is undefined.\n";
            decl_type_final = Object;
        }
    }

    // Need additional actions on let-with-init
    if (init_->type() != No_type){
        // Make sure that a superior type is not assigned to an inferior type
        if (!env.type_LE(init_->type(), decl_type_final)) {
            env.error_env(env.curr_semant_node->klass(), this) << "Inconsistent types in Let initialization: Assign a value of type \"" << init_->type() << "\" to an objectID of type \"" << decl_type_final << "\"\n";

            error_flag = true;
            set_type(Object);
        }
    }

    // Push a new scope into the current Object Scoped Table
    // Temporary: name_ ----mapTo----> decl_type_final
    env.curr_semant_node->otable_.EnterScope();
    env.curr_semant_node->otable_.AddToScope(name_, decl_type_final);

    // Under the current temporary environment, typecheck the body expression of Let
    body_->Typecheck(env);

    // Delete the temporary scope
    env.curr_semant_node->otable_.ExitScope();

    if (!error_flag) {set_type(body_->type()); }
} // end void Let::Typecheck(SemantEnv &env)

void NoExpr::Typecheck(SemantEnv &env) {
    set_type(No_type);
}

void Kase::Typecheck(SemantEnv &env) {
    input_->Typecheck(env);
    Symbol *ans = leaf;

    for (auto branch : *cases_) {
        env.curr_semant_node->otable_.EnterScope();
        env.curr_semant_node->otable_.AddToScope(branch->name_, branch->decl_type_);
        branch->body_->Typecheck(env);
        ans = env.type_LUB(ans, branch->body_->type());
        env.curr_semant_node->otable_.ExitScope();
    }

    set_type(ans);
} // end void Kase::Typecheck(SemantEnv &env)

void UnaryOperator::Typecheck(SemantEnv &env) {
    input_->Typecheck(env);

    switch (kind_) {
        case UnaryOperator::UnaryKind::UO_Not:
            if (input_->type() == Bool) {set_type(Bool); }
            else {
                env.error_env(env.curr_semant_node->klass(), this) <<
                    "\"Not\" operator applied on a non-boolean expression\n";
                set_type(Object);
            }
            break;

        case UnaryOperator::UnaryKind::UO_Neg:
            if (input_->type() == Int) {set_type(Int); }
            else {
                env.error_env(env.curr_semant_node->klass(), this) <<
                    "\"Negation\" operator applied on a non-integer expression\n";
                set_type(Object);
            }
            break;

        case UnaryOperator::UnaryKind::UO_IsVoid:
            set_type(Bool);
            break;

        default:
            break;
    } // end switch
} // end UnaryOperator::Typecheck(SemantEnv &env)

void BinaryOperator::Typecheck(SemantEnv &env) {
    lhs_->Typecheck(env);
    rhs_->Typecheck(env);

    if (kind_ == BinaryKind::BO_Add || kind_ == BinaryKind::BO_Sub
        || kind_ == BinaryKind::BO_Mul || kind_ == BinaryKind::BO_Div)
    // arithmetic operation
    {
        if (lhs_->type() != Int) {
            env.error_env(env.curr_semant_node->klass(), this) << "Left hand side of arithmetic operation should have type \"Int\" but instead has type \"" << lhs_->type() << "\"\n";
            set_type(Object);
        }
        if (rhs_->type() != Int) {
            env.error_env(env.curr_semant_node->klass(), this) << "Right hand side of arithmetic operation should have type \"Int\" but instead has type \"" << rhs_->type() << "\"\n";
            set_type(Object);
        }
        if (lhs_->type() == Int && rhs_->type() == Int) {set_type(Int); }
    } // end if arithmetic operation

    else if (kind_ == BO_LT || kind_ == BO_LE)
    // comparison
    {
        if (lhs_->type() != Int) {
            env.error_env(env.curr_semant_node->klass(), this) << "Left hand side of comparison should have type \"Int\" but instead has type \"" << lhs_->type() << "\"\n";
            set_type(Object);
        }
        if (rhs_->type() != Int) {
            env.error_env(env.curr_semant_node->klass(), this) << "Right hand side of comparison should have type \"Int\" but instead has type \"" << rhs_->type() << "\"\n";
            set_type(Object);
        }
        if (lhs_->type() == Int && rhs_->type() == Int) {set_type(Bool); }
    } // end else if comparison

    else if (kind_ == BO_EQ)
    // equal sign
    {
        bool lit1 = (lhs_->type() == Int) | (lhs_->type() == String)
                    | (lhs_->type() == Bool);
        bool lit2 = (rhs_->type() == Int) | (rhs_->type() == String)
                    | (rhs_->type() == Bool);
        bool lit3 = (lhs_->type() == rhs_->type());
        bool lit_final = (!(lit1 | lit2)) | (lit3);

        if (lit_final) {set_type(Bool); }
        else {
            env.error_env(env.curr_semant_node->klass(), this) << "Inconsistent types in equality expression\n";
            set_type(Object);
        }
    } // end else if equal sign
} // end void BinaryOperator::Typecheck(SemantEnv &env)

void Dispatch::Typecheck(SemantEnv &env) {
    receiver_->Typecheck(env);
    Method *meth_info;

    if (receiver_->type() == SELF_TYPE) { // I really do need to resolve SELF_TYPE here!
        meth_info = env.curr_semant_node->mtable_.Lookup(name_);
    } else {
        meth_info = env.klass_table->ClassFind(receiver_->type())->mtable_.Lookup(name_);
    }

    // Check whether the method name is defined under current class
    if (!meth_info) {
        env.error_env(env.curr_semant_node->klass(), this) << "Cannot call method \"" << name_ << "\" on an object of type \"" << receiver_->type() << "\"\n";
        set_type(Object);
        return;
    }

    const Formals &formals = *meth_info->formals();
    Expressions &actuals = *actuals_;

    // Check whether the dispatch has the right number of arguments
    if (formals.size() != actuals.size()) {
        env.error_env(env.curr_semant_node->klass(), this) << "Method dispatch \"" << name_ << "\" should have " << formals.size() << " arguments but instead " << actuals.size() << " were given\n";

        // Despite the error, typecheck all arguments that are passed as arguments
        for (auto actual : actuals) {actual->Typecheck(env); }
        set_type(Object);
        return;
    } // end if check arugments-size

    auto formal = formals.begin();
    auto formal_end = formals.end();
    auto actual = actuals.begin();
    auto actual_end = actuals.end();
    int i = 1;
    bool error_flag = false;

    // Check whether each argument has the correct type
    while(formal != formal_end && actual != actual_end) {
        (*actual)->Typecheck(env);
        Symbol *type_formal = (*formal)->decl_type();
        Symbol *type_actual = (*actual)->type();

        if (type_actual == SELF_TYPE) {
            type_actual = env.curr_semant_node->klass()->name();
        }

        if (type_formal != type_actual) {
            env.error_env(env.curr_semant_node->klass(), this) << "The " << i << "th/st/nd argument shoud have type \"" << type_formal << "\" but instead has type \"" << type_actual;
            error_flag = true;
        }

        formal++;
        actual++;
        i++;
    } // end while

    if (error_flag) {set_type(Object); }
    else {
        if (meth_info->decl_type() != SELF_TYPE) {set_type(meth_info->decl_type()); }
        else {set_type(receiver_->type()); }
    }

} // end void Dispatch::Typecheck(SemantEnv &env)

void StaticDispatch::Typecheck(SemantEnv &env) {
    receiver_->Typecheck(env);

    // Check the hierarchy of receiver type and dispatch type
    if (!env.type_LUB(receiver_->type(), dispatch_type_)) {
        env.error_env(env.curr_semant_node->klass(), this) << "Cannot dispatch as type \"" << dispatch_type_ << "\"\n";
        set_type(Object);
        return;
    }

    Method *meth_info = env.klass_table->ClassFind(dispatch_type_)->mtable_.Lookup(name_);

    // Check whether the method name is defined under current class
    if (!meth_info) {
        env.error_env(env.curr_semant_node->klass(), this) << "Cannot call method \"" << name_ << "\" on an object of type \"" << receiver_->type() << "\"\n";
        set_type(Object);
        return;
    }

    const Formals &formals = *meth_info->formals();
    Expressions &actuals = *actuals_;

    // Check whether the dispatch has the right number of arguments
    if (formals.size() != actuals.size()) {
        env.error_env(env.curr_semant_node->klass(), this) << "Method dispatch \"" << name_ << "\" should have " << formals.size() << " arguments but instead " << actuals.size() << " were given\n";

        // Despite the error, typecheck all arguments that are passed as arguments
        for (auto actual : actuals) {actual->Typecheck(env); }
        set_type(Object);
        return;
    } // end if check arugments-size

    auto formal = formals.begin();
    auto formal_end = formals.end();
    auto actual = actuals.begin();
    auto actual_end = actuals.end();
    int i = 1;
    bool error_flag = false;

    // Check whether each argument has the correct type
    while(formal != formal_end && actual != actual_end) {
        (*actual)->Typecheck(env);
        Symbol *type_formal = (*formal)->decl_type();
        Symbol *type_actual = (*actual)->type();

        if (type_actual == SELF_TYPE) {
            type_actual = env.curr_semant_node->klass()->name();
        }

        if (type_formal != type_actual) {
            env.error_env(env.curr_semant_node->klass(), this) << "The " << i << "th/st/nd argument shoud have type \"" << type_formal << "\" but instead has type \"" << type_actual;
            error_flag = true;
        }

        formal++;
        actual++;
        i++;
    } // end while

    if (error_flag) {set_type(Object); }
    else {
        if (meth_info->decl_type() != SELF_TYPE) {set_type(meth_info->decl_type()); }
        else {set_type(receiver_->type()); }
    }

} // end void StaticDispatch::Typecheck(SemantEnv &env)


}  // namespace cool
