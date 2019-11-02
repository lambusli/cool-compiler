
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

std::ostream& SemantError::operator()(const SemantNode* node) { return (*this)(node->klass()); }


// Contructor of SemantKlassTable
// Store all the class names that have appeared
SemantKlassTable::SemantKlassTable(SemantError& error, Klasses* klasses)
    : KlassTable(), error_(error) {

    // Pass 1, Part 1: Add classes into SemantKlassTable
    for (auto klass : *klasses) {
        std::cerr << "name:" << klass->name() <<
                     ", parent: " << klass->parent() << std::endl;

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
        //SemantNode *new_node = ClassFind(klass->name());
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
    // Constructor of a semant class table
    SemantKlassTable klass_table(error, program->klasses());
    // Halt program with non-zero exit if there are semantic errors
    if (error.errors()) // If number of errors reported is non-zero
    {
        std::cerr << "Compilation halted due to static semantic errors." << std::endl;
        exit(1);
    }

    // Create scoped-table for method names
    // Why a constructor won't compile but a declaration will work?
    SemantEnv *myEnv = new SemantEnv();
    myEnv->make_big_M();


} // end void Semant(Program* program)




/*
 * Below are all the helper and additional functions declared in semant.h
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

// SemantEnv constructor
SemantEnv::SemantEnv() {}

// Return the pointer to method-name-scoped-table
ScopedTable<Symbol *, Symbol *> &SemantEnv::big_M() {
    return method_scoped_table_;
}

// Create a method-name-scoped-table
void SemantEnv::make_big_M() {
    big_M().EnterScope();
    big_M().AddToScope(in_int, main_meth);

    big_M().EnterScope();
    big_M().AddToScope(in_int, Main);

    big_M().EnterScope();
    big_M().AddToScope(in_int, Int);

    big_M().EnterScope();
    big_M().AddToScope(in_string, String);
    big_M().AddToScope(copy, self);

    std::cout << big_M().Lookup(in_int) << std::endl;
    // std::cout << big_M()->Probe(in_int) << std::endl; // This line reports error, because on the current scope the key is not in_int.
    std::cout << big_M().Probe(in_string) << std::endl;
    std::cout << big_M().Probe(copy) << std::endl;
}


}  // namespace cool
