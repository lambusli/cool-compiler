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
#include "fmt/ostream.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <iostream>

#include "cgen.h"
#include "cgen_supp.h"

Memmgr cgen_Memmgr = GC_NOGC;               // Enable/disable garbage collection
Memmgr_Test cgen_Memmgr_Test = GC_NORMAL;   // Normal/test GC
Memmgr_Debug cgen_Memmgr_Debug = GC_QUICK;  // Check heap frequently

bool cgen_optimize = false;      // Optimize switch for code generator
bool disable_reg_alloc = false;  // Don't do register allocation

extern void emit_string_constant(std::ostream& str, const char* s);

static const char* gc_init_names[] = {"_NoGC_Init", "_GenGC_Init", "_ScnGC_Init"};
static const char* gc_collect_names[] = {"_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect"};

// The following temporary name will not conflict with any
// user-defined names.
#define TEMP1 "_1"

namespace {

//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//////////////////////////////////////////////////////////////////////////////

/// Emit instruction with leading tab for readability
template <typename S, typename... Args>
std::ostream& emit_instr(std::ostream& os, const S& format_str, const Args&... args) {
  // Insert leading tab before every instruction to make assembly more readable
  os << "\t";
  fmt::print(os, format_str, args...);
  return os;
}

std::ostream& emit_load(const char* dest_reg, int offset, const char* source_reg,
                        std::ostream& os) {
  // An example of use fmtlib to print strings using Python like syntax
  return emit_instr(os, "lw {0} {1}({2})\n", dest_reg, offset * WORD_SIZE, source_reg);
}

std::ostream& emit_store(const char* source_reg, int offset, const char* dest_reg,
                         std::ostream& os) {
  return emit_instr(os, "sw {2} {1}({0})\n", dest_reg, offset * WORD_SIZE, source_reg);
}

std::ostream& emit_load_imm(const char* dest_reg, int val, std::ostream& os) {
  return emit_instr(os, "li {} {}\n", dest_reg, val);
}

std::ostream& emit_load_address(const char* dest_reg, const char* address, std::ostream& os) {
  return emit_instr(os, "la {} {}\n", dest_reg, address);
}

std::ostream& emit_partial_load_address(const char* dest_reg, std::ostream& os) {
  return emit_instr(os, "la {} ", dest_reg);
}

std::ostream& emit_move(const char* dest_reg, const char* source_reg, std::ostream& os) {
  if (regEq(dest_reg, source_reg)) {
    spdlog::debug("Omitting move from {} to {}", source_reg, dest_reg);
    return os;
  }
  return emit_instr(os, "move {} {}\n", dest_reg, source_reg);
}

std::ostream& emit_neg(const char* dest, const char* src1, std::ostream& os) {
  return emit_instr(os, "neg {} {}\n", dest, src1);
}

std::ostream& emit_binop(const char* op, const char* dest, const char* src1, const char* src2,
                         std::ostream& os) {
  return emit_instr(os, "{} {} {} {}\n", op, dest, src1, src2);
}

std::ostream& emit_add(const char* dest, const char* src1, const char* src2, std::ostream& os) {
  return emit_binop("add", dest, src1, src2, os);
}

std::ostream& emit_addu(const char* dest, const char* src1, const char* src2, std::ostream& os) {
  return emit_binop("addu", dest, src1, src2, os);
}

std::ostream& emit_addiu(const char* dest, const char* src1, int imm, std::ostream& os) {
  return emit_instr(os, "addiu {} {} {}\n", dest, src1, imm);
}

std::ostream& emit_div(const char* dest, const char* src1, const char* src2, std::ostream& os) {
  return emit_binop("div", dest, src1, src2, os);
}

std::ostream& emit_mul(const char* dest, const char* src1, const char* src2, std::ostream& os) {
  return emit_binop("mul", dest, src1, src2, os);
}

std::ostream& emit_sub(const char* dest, const char* src1, const char* src2, std::ostream& os) {
  return emit_binop("sub", dest, src1, src2, os);
}

std::ostream& emit_sll(const char* dest, const char* src1, int num, std::ostream& os) {
  return emit_instr(os, "sll {} {} {}\n", dest, src1, num);
}

std::ostream& emit_jalr(const char* dest, std::ostream& os) {
  return emit_instr(os, "jalr {}\n", dest);
}

std::ostream& emit_return(std::ostream& os) {
  return emit_instr(os, "jr $ra\n");
}

std::ostream& emit_jal_to_label(const char* label, std::ostream& os) {
  return emit_instr(os, "jal {}\n", label);
}

std::ostream& emit_copy(std::ostream& os) { return emit_jal_to_label("Object.copy", os); }

std::ostream& emit_gc_assign(std::ostream& os) { return emit_jal_to_label("_GenGC_Assign", os); }

std::ostream& emit_equality_test(std::ostream& os) {
  return emit_jal_to_label("equality_test", os);
}

std::ostream& emit_case_abort(std::ostream& os) { return emit_jal_to_label("_case_abort", os); }

std::ostream& emit_case_abort2(std::ostream& os) { return emit_jal_to_label("_case_abort2", os); }

std::ostream& emit_dispatch_abort(std::ostream& os) {
  return emit_jal_to_label("_dispatch_abort", os);
}

std::ostream& emit_label_ref(int l, std::ostream& os) {
  os << "label" << l;
  return os;
}

std::ostream& emit_label_def(int l, std::ostream& os) {
  emit_label_ref(l, os) << ":" << std::endl;
  return os;
}

std::ostream& emit_beqz(const char* source, int label, std::ostream& os) {
  return emit_instr(os, "beqz {} label{}\n", source, label);
}

std::ostream& emit_beq(const char* src1, const char* src2, int label, std::ostream& os) {
  return emit_instr(os, "beq {} {} label{}\n", src1, src2, label);
}

std::ostream& emit_bne(const char* src1, const char* src2, int label, std::ostream& os) {
  return emit_instr(os, "bne {} {} label{}\n", src1, src2, label);
}

std::ostream& emit_bleq(const char* src1, const char* src2, int label, std::ostream& os) {
  return emit_instr(os, "ble {} {} label{}\n", src1, src2, label);
}

std::ostream& emit_blt(const char* src1, const char* src2, int label, std::ostream& os) {
  return emit_instr(os, "blt {} {} label{}\n", src1, src2, label);
}

std::ostream& emit_blti(const char* src1, int imm, int label, std::ostream& os) {
  return emit_instr(os, "blt {} {} label{}\n", src1, imm, label);
}

std::ostream& emit_bgti(const char* src1, int imm, int label, std::ostream& os) {
  return emit_instr(os, "bgt {} {} label{}\n", src1, imm, label);
}

std::ostream& emit_branch(int label, std::ostream& os) {
  return emit_instr(os, "b label{}\n", label);
}

/// Push a register on the stack. The stack grows towards smaller addresses.
std::ostream& emit_push(const char* reg, std::ostream& os) {
  emit_store(reg, 0, SP, os);
  emit_addiu(SP, SP, -4, os);
  return os;
}

/// Fetch the integer value in an Int object.
std::ostream& emit_fetch_int(const char* dest, const char* source, std::ostream& os) {
  return emit_load(dest, DEFAULT_OBJFIELDS, source, os);
}

/// Update the integer value in an int object.
std::ostream& emit_store_int(const char* source, const char* dest, std::ostream& os) {
  return emit_store(source, DEFAULT_OBJFIELDS, dest, os);
}

std::ostream& emit_gc_check(const char* source, std::ostream& os) {
  if (source != A1) {
    emit_move(A1, source, os);
  }
  return emit_jal_to_label("_gc_check", os);
}

}  // namespace

namespace cool {

bool gCgenDebug = false;

int num_label = 0;
int num_temp = 0;  // number of temporals in a method body

// clang-format off
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
// clang-format on

namespace {

/// Emit label for prototype object of class
std::ostream& emit_protobj_ref(Symbol* sym, std::ostream& os) {
  return os << sym << PROTOBJ_SUFFIX;
}

/// Emit label for dispatch table of class
std::ostream& emit_disptable_ref(Symbol* sym, std::ostream& os) {
  return os << sym << DISPTAB_SUFFIX;
}

/// Emit label for method of a class
std::ostream& emit_method_ref(Symbol* classname, Symbol* methodname, std::ostream& os) {
  return os << classname << METHOD_SEP << methodname;
}

/// Emit label for initialization code for a class
std::ostream& emit_init_ref(Symbol* sym, std::ostream& os) { return os << sym << CLASSINIT_SUFFIX; }

/// Emit JAL to class initialization code
std::ostream& emit_init(Symbol* classname, std::ostream& os) {
  os << JAL;
  return emit_init_ref(classname, os) << std::endl;
}

/**
 * Generate reference to label for String constant
 * @param os std::ostream to write generated code to
 * @param entry String constant
 * @return os
 */
std::ostream& CgenRef(std::ostream& os, const StringEntry* entry) {
  os << STRCONST_PREFIX << entry->id();
  return os;
}

/**
 * Generate reference to label for Int constant
 * @param os std::ostream to write generated code to
 * @param entry Int constant
 * @return os
 */
std::ostream& CgenRef(std::ostream& os, const Int32Entry* entry) {
  os << INTCONST_PREFIX << entry->id();
  return os;
}

/**
 * Generate reference to label for Bool constant
 * @param os std::ostream to write generated code to
 * @param entry Bool constant
 * @return os
 */
std::ostream& CgenRef(std::ostream& os, bool entry) {
  os << BOOLCONST_PREFIX << ((entry) ? 1 : 0);
  return os;
}


/**
 * @brief Emit definition of string constant labeled by index in the gStringTable
 * @param os std::ostream to write generated code to
 * @param entry String constant
 * @param class_tag String class tag
 * @return os
 */
std::ostream& CgenDef(std::ostream& os, const StringEntry* entry, std::size_t class_tag) {
  const std::string& value = entry->value();
  auto length_entry = gIntTable.emplace(value.size());

  // Add -1 eye catcher
  os << WORD << "-1" << std::endl;
  CgenRef(os, entry) << LABEL;
  os << WORD << class_tag << std::endl
     << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (value.size() + 4) / 4) << std::endl  // size
     << WORD;
  emit_disptable_ref(String, os) << std::endl;
  os << WORD;
  CgenRef(os, length_entry) << std::endl;
  emit_string_constant(os, value.c_str());
  os << ALIGN;
  return os;
}

/**
 * @brief Emit definition of integer constant labeled by index in the gIntTable
 * @param os std::ostream to write generated code to
 * @param entry Int constant
 * @param class_tag Int class tag
 * @return os
 */
std::ostream& CgenDef(std::ostream& os, const Int32Entry* entry, std::size_t class_tag) {
  // Add -1 eye catcher
  os << WORD << "-1" << std::endl;
  CgenRef(os, entry) << LABEL;
  os << WORD << class_tag << std::endl
     << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << std::endl
     << WORD;
  emit_disptable_ref(Int, os) << std::endl;
  os << WORD << entry->value() << std::endl;
  return os;
}

/**
 * @brief Emit definition of a bool constant
 * @param os std::ostream to write generated code to
 * @param entry Bool constant
 * @param class_tag Bool class tag
 * @return
 */
std::ostream& CgenDef(std::ostream& os, bool entry, std::size_t class_tag) {
  // Add -1 eye catcher
  os << WORD << "-1" << std::endl;
  CgenRef(os, entry) << LABEL;
  os << WORD << class_tag << std::endl
     << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << std::endl
     << WORD;
  emit_disptable_ref(Bool, os) << std::endl;
  os << WORD << ((entry) ? 1 : 0) << std::endl;
  return os;
}

/**
 * @brief Generate definitions for the constants in a SymbolTable
 * @param os std::ostream to write generated code to
 * @param table SymbolTable of constants, e.g. gIntTable
 * @param class_tag Class tag for the type of constant being generated
 * @return os
 */
template <class Elem>
std::ostream& CgenDef(std::ostream& os, const SymbolTable<Elem>& table, size_t class_tag) {
  std::vector<Elem*> values;
  for (const auto& value : table) {
    values.push_back(value.second.get());
  }
  // Reverse sort by index to maintain backward compatibility with cool
  std::sort(values.begin(), values.end(),
            [](const Elem* lhs, const Elem* rhs) { return lhs->id() > rhs->id(); });
  for (const auto& value : values) {
    CgenDef(os, value, class_tag);
  }
  return os;
}


}  // anonymous namespace


CgenKlassTable::CgenKlassTable(Klasses* klasses) {
  InstallClasses(klasses);

    // Add your code to:
    // 1. Build inheritance graph
    // 2. Initialize the node tags and other information you need
    int val = 0;
    for (auto node : nodes_) {
        CgenNode *parent_node = ClassFind(node->parent_name());
        node->parent_ = parent_node;
        parent_node->children_.push_back(node);
        node->tag_ = val;
        val++;
        gStringTable.emplace(node->name()->value());
    } // end for
} // end CgenKlassTable constructor


void CgenKlassTable::CgenGlobalData(std::ostream& os) const {
  Symbol* main = gIdentTable.emplace(MAINNAME);
  Symbol* string = gIdentTable.emplace(STRINGNAME);
  Symbol* integer = gIdentTable.emplace(INTNAME);
  Symbol* boolc = gIdentTable.emplace(BOOLNAME);

  os << "\t.data\n" << ALIGN;

  // The following global names must be defined first.
  os << GLOBAL << CLASSNAMETAB << std::endl;
  os << GLOBAL;
  emit_protobj_ref(main, os);
  os << std::endl;
  os << GLOBAL;
  emit_protobj_ref(integer, os);
  os << std::endl;
  os << GLOBAL;
  emit_protobj_ref(string, os);
  os << std::endl;
  os << GLOBAL << BOOLCONST_PREFIX << 0 << std::endl;
  os << GLOBAL << BOOLCONST_PREFIX << 1 << std::endl;
  os << GLOBAL << INTTAG << std::endl;
  os << GLOBAL << BOOLTAG << std::endl;
  os << GLOBAL << STRINGTAG << std::endl;

  // We also need to know the tag of the Int, String, and Bool classes
  // during code generation.
  os << INTTAG << LABEL << WORD << TagFind(integer) << std::endl;
  os << BOOLTAG << LABEL << WORD << TagFind(boolc) << std::endl;
  os << STRINGTAG << LABEL << WORD << TagFind(string) << std::endl;
}

void CgenKlassTable::CgenSelectGC(std::ostream& os) const {
  os << GLOBAL << "_MemMgr_INITIALIZER" << std::endl;
  os << "_MemMgr_INITIALIZER:" << std::endl;
  os << WORD << gc_init_names[cgen_Memmgr] << std::endl;
  os << GLOBAL << "_MemMgr_COLLECTOR" << std::endl;
  os << "_MemMgr_COLLECTOR:" << std::endl;
  os << WORD << gc_collect_names[cgen_Memmgr] << std::endl;
  os << GLOBAL << "_MemMgr_TEST" << std::endl;
  os << "_MemMgr_TEST:" << std::endl;
  os << WORD << (cgen_Memmgr_Test == GC_TEST) << std::endl;
}

void CgenKlassTable::CgenConstants(std::ostream& os) const {
  // Make sure "default" values are in their respective tables
  gStringTable.emplace("");
  gIntTable.emplace(0);

  std::size_t string_tag = TagFind(String), int_tag = TagFind(Int), bool_tag = TagFind(Bool);
  CgenDef(os, gStringTable, string_tag);
  CgenDef(os, gIntTable, int_tag);
  CgenDef(os, false, bool_tag);
  CgenDef(os, true, bool_tag);
}


void CgenKlassTable::CgenGlobalText(std::ostream& os) const {
  os << GLOBAL << HEAP_START << std::endl
     << HEAP_START << LABEL << WORD << 0 << std::endl
     << "\t.text" << std::endl
     << GLOBAL;
  emit_init_ref(Main, os);
  os << std::endl << GLOBAL;
  emit_init_ref(Int, os);
  os << std::endl << GLOBAL;
  emit_init_ref(String, os);
  os << std::endl << GLOBAL;
  emit_init_ref(Bool, os);
  os << std::endl << GLOBAL;
  emit_method_ref(Main, main_meth, os);
  os << std::endl;
}

// While it would seem natural for this to be a const method, the process of code generation
// modifies the nodes in the KlassTable.
void CgenKlassTable::CodeGen(std::ostream& os) {
  CgenGlobalData(os);
  CgenSelectGC(os);
  CgenConstants(os);

  // Do all the varBinding
  allBinding();

  // Add your code to emit:
  // 1. Prototype objects
  CgenProtobj(os);
  // 2. class_nameTab and class_objTab
  CgenClassNameTable(os);
  CgenClassObjTable(os);
  // 3. Dispatch tables for each class
  CgenDispTable(os);

  CgenGlobalText(os);

  // Add your code to emit:
  // 1. Object initializers for each class  (xxx.init())
  CgenObjInit(os);
  // 2. Class methods
  CgenMethBody(os);

}


void Cgen(Program* program, std::ostream& os) {
  CgenKlassTable klass_table(program->klasses());
  klass_table.CodeGen(os);
}




/*
 *************************
 * Additional methods
 *************************
 */

/*
 * Part I
 * Emission of global tables
 * Preparatory methods (varBinding, CgenEnv, ...)
 */

// Emit class nametable
void CgenKlassTable::CgenClassNameTable(std::ostream& os) const {
    os << CLASSNAMETAB << LABEL;

    for (auto node : nodes_) {
        os << WORD;
        CgenRef(os, gStringTable.lookup(node->name()));
        os << std::endl;
    } // end for
} // end void CgenKlassTable::CgenClassNameTable(std::ostream& os) const


// Emit class objtable
void CgenKlassTable::CgenClassObjTable(std::ostream& os) const {
    os << CLASSOBJTAB << LABEL;

    for (auto node : nodes_) {
        os << WORD;
        emit_protobj_ref(node->name(), os);
        os << std::endl;

        os << WORD;
        emit_init_ref(node->name(), os);
        os << std::endl;
    } // end for
} // end void CgenKlassTable::CgenClassObjTable(std::ostream& os) const


// Emit Prototype object
void CgenKlassTable::CgenProtobj(std::ostream& os) const {
    for (auto node : nodes_) {
        // Garbage collector tag, offset = -4
        os << WORD << -1 << std::endl;

        // title
        emit_protobj_ref(node->name(), os);
        os << LABEL;

        // Class tag, offset 0
        os << WORD << node->tag_ << std::endl;

        // Object size, offset 4
        // components: attributes, tag, dispatch pointer, garbage collector
        os << WORD << node->evector_attr_.size() + 3 << std::endl;

        // Dispatch pointer, offset 8
        os << WORD;
        emit_disptable_ref(node->name(), os);
        os << std::endl;

        // Attributes, offset 12+
        for (auto attr_name : node->evector_attr_) {
            os << WORD;
            auto entry = node->etable_var_.Lookup(attr_name);

            if (entry->decl_type_ == String) {
                CgenRef(os, gStringTable.emplace(""));
            }
            else if (entry->decl_type_ == Int) {
                CgenRef(os, gIntTable.emplace(0));
            }
            else if (entry->decl_type_ == Bool) {
                CgenRef(os, false);
            }
            else {
                os << 0;
            }

            os << std::endl;
        } // end for
    } // end for
} // end void CgenKlassTable::CgenProtobj(std::ostream& os) const


// Emit dispatch table
void CgenKlassTable::CgenDispTable(std::ostream& os) const {
    for (auto node : nodes_) {
        os << node->name() << DISPTAB_SUFFIX << LABEL;

        for (auto meth_name : node->evector_meth_) {
            auto entry = node->etable_meth_[meth_name];
            os << WORD << entry->class_name_ << "." << meth_name << std::endl;
        }

    } // end for
} // end void CgenKlassTable::CgenDispTable(std::ostream& os) const


// Varbinding for all CgenNode
void CgenKlassTable::allBinding() {
    doBinding(root(), NULL);
}


// Recursive do varbinding for each CgenNode
void CgenKlassTable::doBinding(CgenNode *node, CgenNode *parent) {
    // Starting from offset 12, we store attributes
    int attr_offset = 12;
    // Offset for methods in dispatch table
    int meth_offset = 0;

    // Inheritance: duplicate the etables and evectors from parent to node
    if (parent) {
        node->etable_var_ = parent->etable_var_;
        node->evector_attr_ = parent->evector_attr_;
        node->etable_meth_ = parent->etable_meth_;
        node->evector_meth_ = parent->evector_meth_;
        attr_offset += 4 * node->evector_attr_.size();
        meth_offset += 4 * node->etable_meth_.size();
    }

    node->etable_var_.EnterScope();

    // traverse each feature of this CgenNode
    for (auto feature : *node->klass()->features()) {
        if (feature->attr())
        // operation if feature is attribute
        {
            node->evector_attr_.push_back(feature->name());

            VarBinding *vb = new VarBinding();
            vb->class_name_ = node->name();
            vb->var_name_ = feature->name();
            vb->decl_type_ = feature->decl_type();
            vb->origin_ = ATTR;
            vb->offset_ = attr_offset;

            attr_offset += 4;

            node->etable_var_.AddToScope(feature->name(), vb);

        } else
        // operation if feature is method
        {
            Method *meth = (Method *)feature;

            MethBinding *mb = new MethBinding();
            mb->class_name_ = node->name();
            mb->meth_name_ = meth->name();
            mb->decl_type_ = meth->decl_type();
            mb->num_arg_ = meth->formals()->size();

            // only insert meth_name into vector and bind a new offset
            // if the method was not defined in a parent class
            if (node->etable_meth_[meth->name()] == NULL) {
                node->evector_meth_.push_back(meth->name());
                mb->offset_ = meth_offset;
                meth_offset += 4;
            }
            // if a method is redefined, the offset does not change
            else {
                mb->offset_ = node->etable_meth_[meth->name()]->offset_;
            }

            // Bind method to etable_meth_
            node->etable_meth_[feature->name()] = mb;
        }
    } // end for

    // Recursively doBinding for all children
    for (auto child : node->children_) {
        doBinding(child, node);
    }
} // end void CgenKlassTable::doBinding(CgenNode *node, CgenNode *parent)


// Constructor of CgenEnv
CgenEnv::CgenEnv(CgenKlassTable *klass_table_arg,
        CgenNode *curr_cgen_node_arg,
        std::ostream &os_arg) :
        klass_table(klass_table_arg),
        curr_cgen_node(curr_cgen_node_arg),
        os(os_arg) {}



/*
 * Part II
 * Helper functions of code generation
 */

// Callee prologue
void prologue(std::ostream &os) {
    // move stack pointer 3 words down
    os << ADDIU << SP << " " << SP << " -12\n";
    // store the address of the old framepointer as the first record
    os << SW << FP << " 12(" << SP << ")\n" ;
    // store the address of caller's self as the second record
    os << SW << SELF << " 8(" << SP << ")\n";
    // store the caller's return address as the third record
    os << SW << RA << " 4(" << SP << ")\n";
    // create the new framepointer
    os << ADDIU << FP << " " << SP << " 4\n";
    // place callee's self in $s0
    // callee's self is already in $a0 at some point
    os << MOVE << SELF << " " << ACC << "\n";
} // end void prologue(std::ostream &os)


// Callee epilogue for object initializer
void epilogue_init(std::ostream &os) {
    // Place callee's self in the accumulator
    os << MOVE << ACC << " " << SELF << "\n";
    // Restore the old framepointer
    os << LW << FP << " 12(" << SP << ")\n";
    // Restore the caller's self
    os << LW << SELF << " 8(" << SP << ")\n";
    // Place the return address in $ra
    os << LW << RA << " 4(" << SP << ")\n";
    // Pop stackframe
    os << ADDIU << SP << " " << SP << " 12\n";
    // Jump to the return address
    os << RET << "\n";
} // void epilogue(std::ostream &os)


// General epilogue
void epilogue_general(std::ostream &os, int num_arg) {
    // Restore the old framepointer
    os << LW << FP << " 12(" << SP << ")\n";
    // Restore the caller's self
    os << LW << SELF << " 8(" << SP << ")\n";
    // Place the return address in $ra
    os << LW << RA << " 4(" << SP << ")\n";
    // Pop stackframe (both callee's save and callee's arguments)
    os << ADDIU << SP << " " << SP << " " << 12 + 4 * num_arg << "\n";
    // Jump to the return address
    os << RET << "\n";
} // end void epilogue_general(std::ostream &os)


// Check whether a method of a class is already predefined
bool method_is_predefined(Symbol *class_name, Symbol *method_name) {
    if (class_name == Object && method_name == copy) {return true; }
    if (class_name == Object && method_name == cool_abort) {return true; }
    if (class_name == Object && method_name == type_name) {return true; }
    if (class_name == IO && method_name == out_string) {return true; }
    if (class_name == IO && method_name == out_int) {return true; }
    if (class_name == IO && method_name == in_string) {return true; }
    if (class_name == IO && method_name == in_int) {return true; }
    if (class_name == String && method_name == length) {return true; }
    if (class_name == String && method_name == concat) {return true; }
    if (class_name == String && method_name == substr) {return true; }
    return false;
} // end bool method_is_predefined(Symbol *class_name, Symbol *method_name)


// Count temporals of a method body
void Method::CountTemporal(int &num_temp, int &max_temp) {
    body_->CountTemporal(num_temp, max_temp);
}


// Count temporals of a block
void Block::CountTemporal(int &num_temp, int &max_temp) {
    for (auto expr : *body_) {
        expr->CountTemporal(num_temp, max_temp);
    }
}


// Count temporals of a LET AST node
void Let::CountTemporal(int &num_temp, int &max_temp) {
    num_temp++;
    if (num_temp > max_temp) {max_temp = num_temp; }
    body_->CountTemporal(num_temp, max_temp);
    num_temp--;
}





/*
 * Part III
 * Code generation
 */

// Emite all object initializers
void CgenKlassTable::CgenObjInit(std::ostream &os) {
    for (auto node : nodes_) {
        os << node->name() << CLASSINIT_SUFFIX << LABEL;
        prologue(os); // callee prologue

        // initialze parent object
        if (node->parent()->name() != No_class) {
            os << JAL << node->parent()->name() << CLASSINIT_SUFFIX << "\n";
        }

        // Create Cgen for a specific class
        CgenEnv envnow(this, node, os);

        // If an attribute is initialized, we need to store the value in the stackframe
        for (auto feature : *node->klass()->features()) {
            // Do nothing for a method
            if (feature->method()) {continue; }

            Attr *attr = (Attr *)feature;
            // Do nothing if an attribute is not initialized
            if (!attr->init()->IsCode()) {continue; }

            // Codegen for the initialized value
            attr->init()->CodeGen(envnow);
            // Store the value at the correct offset
            os << SW << ACC << " " << node->etable_var_.Lookup(feature->name())->offset_
               << "(" << SELF << ")\n";
        }

        epilogue_init(os); // callee epilogue
    } // end for
} // end CgenKlassTable::CgenObjInit(std::ostream &os) const


// Code generation for all class attributes and methods
void CgenKlassTable::CgenMethBody(std::ostream &os) {
    for (auto node : nodes_) {
        for (auto feature : *node->klass()->features()) {
            // Generate code only for method bodies
            // Do nothing for an attribute
            if (feature->attr()) {continue; }

            Method *meth = (Method *)feature;

            // Bypass all the internally defined methods
            if (method_is_predefined(node->name(), meth->name())) {continue; }

            // Count number of words we need to store temporals
            int max_temp = 0;
            meth->CountTemporal(num_temp, max_temp);

            // Enter a temporary scope for method arguments
            node->etable_var_.EnterScope();

            // Create a new VarBindings in the new scope for each method arg
            // Calculate the offset of each argument relative to framepointer
            // offset of 1st arg: 8 + 4 * num_arg + 4 * max_temp
            // offset of 2nd arg: 8 + 4 * (num_arg - 1) + 4 * max_temp
            // ...
            // offset of the last arg: 12 + 4 * max_temp
            int arg_offset = 8 + 4 * meth->formals()->size() + 4 * max_temp;
            for (auto formal : *meth->formals()) {
                VarBinding *vb = new VarBinding();
                vb->class_name_ = node->name();
                vb->var_name_ = formal->name();
                vb->decl_type_ = formal->decl_type();
                vb->origin_ = ARG;
                vb->offset_ = arg_offset;
                arg_offset -= 4;
                node->etable_var_.AddToScope(formal->name(), vb);
            }

            // Create Cgen environment for a specific class
            CgenEnv envnow(this, node, os);

            // title label
            os << node->name() << "." << meth->name() << LABEL;

            // Prologue
            prologue(os);

            meth->body_->CodeGen(envnow);

            // epilogue
            epilogue_general(os, node->etable_meth_[meth->name()]->num_arg_);

            // Exit the temporary scope for method args
            node->etable_var_.ExitScope();

        } // end for feature
    } // end for node
} // end CgenKlassTable::CgenMethBody(std::ostream &os) const

void NoExpr::CodeGen(CgenEnv &env) {}


void IntLiteral::CodeGen(CgenEnv &env) {
    env.os << LA << ACC << " ";
    CgenRef(env.os, gIntTable.emplace(value()));
    env.os << std::endl;
}


void StringLiteral::CodeGen(CgenEnv &env) {
    env.os << LA << ACC << " ";
    CgenRef(env.os, gStringTable.emplace(value()));
    env.os << std::endl;
}


void BoolLiteral::CodeGen(CgenEnv &env) {
    env.os << LA << ACC << " ";
    CgenRef(env.os, value());
    env.os << std::endl;
}


void Dispatch::CodeGen(CgenEnv &env) {
    CgenNode *receiver_cgen_node;

    // Evaluate each argument and push it into current stackframe
    for (auto actual : *actuals_) {
        actual->CodeGen(env);
        env.os << SW << ACC << " 0(" << SP << ")\n";
        env.os << ADDIU << SP << " " << SP << " -4\n";
    }

    receiver_->CodeGen(env);

    // Evaluate the receiver object and load it into accumulator
    if (receiver_->type() == SELF_TYPE) {
        receiver_cgen_node = env.curr_cgen_node;
    } else {
        receiver_cgen_node = env.klass_table->ClassFind(receiver_->type());
    }

    // Check whether the receiver object is NULL, and then branch
    env.os << BNE << ACC << " " << ZERO << " label" << num_label << "\n";

    // Abort if receiver is NULL
    // Load filename into ACC
    env.os << LA << ACC << " ";
    CgenRef(env.os, gStringTable.lookup(env.curr_cgen_node->filename()->value()));
    env.os << "\n";
    // Load line number into T1
    env.os << LI << T1 << " " << loc() << "\n";
    // Abort
    emit_dispatch_abort(env.os);

    // Jump
    env.os << "label" << num_label << LABEL;
    num_label++;
    // Load the dispatch pointer into $t1
    env.os << LW << T1 << " 8(" << ACC << ")\n";
    // Find the offset of the method and load into $t1
    env.os << LW << T1 << " " << receiver_cgen_node->etable_meth_[name_]->offset_ << "(" << T1 << ")\n";
    // execute dispatch
    env.os << JALR << T1 << "\n";

} // end void Dispatch::CodeGen(CgenEnv &env)


void Ref::CodeGen(CgenEnv &env) {
    // if ID is the "self" key word
    if (name_ == self) {
        env.os << MOVE << ACC << " " << SELF << "\n";
    }
    // if ID is anything else
    else {
        VarBinding *target = env.curr_cgen_node->etable_var_.Lookup(name_);
        int origin  = target->origin_;
        int offset = target->offset_;

        switch (origin) {
            case ATTR:
                env.os << LW << ACC << " " << offset << "(" << SELF << ")\n";
                break;
            case ARG:
                env.os << LW << ACC << " " << offset << "(" << FP << ")\n";
                break;
            default:
                break;
        } // end switch
    } // end else

} // end void Ref::CodeGen(CgenEnv &env)


void Block::CodeGen(CgenEnv &env) {
    for (auto expr : *body_) {
        expr->CodeGen(env);
    }
} // end void Block::CodeGen(CgenEnv &env)


void Knew::CodeGen(CgenEnv &env) {
    if (name_ == SELF_TYPE) {
        // Load the pointer to Object Table into $t1
        env.os << LA << T1 << " " << CLASSOBJTAB << "\n";
        // Load the tag of the class (referred to by self) into $t2
        // Tag is at offset 0 of prototype object
        env.os << LW << T2 << " 0(" << SELF << ")\n";
        // In class Object Table, the offset of a prototype object pointer
        // = 8 * tag_number
        // Increament $t1 by this number, so that $t1 points to the prototype object we want
        env.os << SLL << T2 << " " << T2 << " 3\n";
        env.os << ADD << T1 << " " << T1 << " " << T2 << "\n";
        // Push the address of prototype object we want temporarily onto Stack
        env.os << SW << T1 << " 0(" << SP << ")\n";
        env.os << ADDIU << SP << " " << SP << " -4\n";
        // Load the tag value of the prototype object into ACC (at offset 0)
        // Prepare for copying and creating new object
        env.os << LW << ACC << " 0(" << T1 << ")\n";
        // Copy and create new object
        env.os << JAL << "Object.copy\n";
        // Load the pointer to the prototype object into $t1
        env.os << LW << T1 << " 4(" << SP << ")\n";
        // Load the pointer to object initializer (offset 4) into t1
        // !! I don't buy this
        env.os << LW << T1 << " 4(" << T1 << ")\n";
        // Jump to init
        env.os << JALR << T1 << "\n";

        // Pop the temporary from the stack
        env.os << ADDIU << SP << " " << SP << " 4\n";
    } else {
        // Load the prototype object into accumulator
        env.os << LA << ACC << " " << name_ << PROTOBJ_SUFFIX << "\n";
        // Copy Object
        env.os << JAL << "Object.copy\n";
        // Init itself
        env.os << JAL << name_ << CLASSINIT_SUFFIX << "\n";
    }
} // end void Knew::CodeGen(CgenEnv &env)


void Assign::CodeGen(CgenEnv &env) {
    value_->CodeGen(env);

    VarBinding *target = env.curr_cgen_node->etable_var_.Lookup(name_);
    int origin  = target->origin_;
    int offset = target->offset_;

    switch (origin) {
        case ATTR:
            env.os << SW << ACC << " " << offset << "(" << SELF << ")\n";
            break;
        case ARG:
            env.os << SW << ACC << " " << offset << "(" << FP << ")\n";
            break;
        default:
            break;
    }
} // end void Assign::CodeGen(CgenEnv &env)


void BinaryOperator::CodeGen(CgenEnv &env) {
    int merge_label;
    // eval lhs
    lhs_->CodeGen(env);
    // store the result of lhs temporarily on the stack
    env.os << SW << ACC << " 0(" << SP << ")\n";
    env.os << ADDIU << SP << " " << SP << " -4\n";
    // eval rhs
    rhs_->CodeGen(env);

    switch (kind_) {
        // Plus
        case BO_Add:
            // Make a copy object that will store the new calculated result
            env.os << JAL << "Object.copy\n";
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the actual value of lhs into $t1. The value is at offset 12
            env.os << LW << T1 << " 12(" << T1 << ")\n";
            // Load the actual value of rhs into $t2.
            env.os << LW << T2 << " 12(" << ACC << ")\n";
            // perform addition
            env.os << ADD << T1 << " " << T1 << " " << T2 << "\n";
            // store the new result in the copied object, at offset 12
            env.os << SW << T1 << " 12(" << ACC << ")\n";
            break;

        // minus
        case BO_Sub:
            // Make a copy object that will store the new calculated result
            env.os << JAL << "Object.copy\n";
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the actual value of lhs into $t1. The value is at offset 12
            env.os << LW << T1 << " 12(" << T1 << ")\n";
            // Load the actual value of rhs into $t2.
            env.os << LW << T2 << " 12(" << ACC << ")\n";
            // perform subtraction
            env.os << SUB << T1 << " " << T1 << " " << T2 << "\n";
            // store the new result in the copied object, at offset 12
            env.os << SW << T1 << " 12(" << ACC << ")\n";
            break;

        // multiply
        case BO_Mul:
            // Make a copy object that will store the new calculated result
            env.os << JAL << "Object.copy\n";
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the actual value of lhs into $t1. The value is at offset 12
            env.os << LW << T1 << " 12(" << T1 << ")\n";
            // Load the actual value of rhs into $t2.
            env.os << LW << T2 << " 12(" << ACC << ")\n";
            // perform multiplication
            env.os << MUL << T1 << " " << T1 << " " << T2 << "\n";
            // store the new result in the copied object, at offset 12
            env.os << SW << T1 << " 12(" << ACC << ")\n";
            break;

        // divide
        case BO_Div:
            // Make a copy object that will store the new calculated result
            env.os << JAL << "Object.copy\n";
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the actual value of lhs into $t1. The value is at offset 12
            env.os << LW << T1 << " 12(" << T1 << ")\n";
            // Load the actual value of rhs into $t2.
            env.os << LW << T2 << " 12(" << ACC << ")\n";
            // perform division
            env.os << DIV << T1 << " " << T1 << " " << T2 << "\n";
            // store the new result in the copied object, at offset 12
            env.os << SW << T1 << " 12(" << ACC << ")\n";
            break;

        // less than
        case BO_LT:
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the actual value of lhs into $t1. The value is at offset 12
            env.os << LW << T1 << " 12(" << T1 << ")\n";
            // Load the actual value of rhs into $t2.
            env.os << LW << T2 << " 12(" << ACC << ")\n";
            // Assume true
            env.os << LA << ACC << " ";
            CgenRef(env.os, true);
            env.os << "\n";
            // If really true, jump away
            merge_label = num_label;
            num_label++;
            env.os << BLT << T1 << " " << T2 << " label" << merge_label << "\n";
            // Set the boolean to be false
            env.os << LA << ACC << " ";
            CgenRef(env.os, false);
            env.os << "\n";
            // Conclude with the merging label
            env.os << "label" << merge_label << LABEL;
            break;

        // less or equal to
        case BO_LE:
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the actual value of lhs into $t1. The value is at offset 12
            env.os << LW << T1 << " 12(" << T1 << ")\n";
            // Load the actual value of rhs into $t2.
            env.os << LW << T2 << " 12(" << ACC << ")\n";
            // Assume true
            env.os << LA << ACC << " ";
            CgenRef(env.os, true);
            env.os << "\n";
            // If really true, jump away
            merge_label = num_label;
            num_label++;
            env.os << BLEQ << T1 << " " << T2 << " label" << merge_label << "\n";
            // Set the boolean to be false
            env.os << LA << ACC << " ";
            CgenRef(env.os, false);
            env.os << "\n";
            // Conclude with the merging label
            env.os << "label" << merge_label << LABEL;
            break;

        // equal to
        case BO_EQ:
            // Load the reference of lhs into $t1
            env.os << LW << T1 << " 4(" << SP << ")\n";
            // Load the reference of rhs into $t2
            env.os << MOVE << T2 << " " << ACC << "\n";
            // Load the reference of "true" into $a0
            env.os << LA << ACC << " ";
            CgenRef(env.os, true);
            env.os << "\n";
            // jump if the pointers to lhs and rhs are equal
            merge_label = num_label;
            num_label++;
            env.os << BEQ << T1 << " " << T2 << " label" << merge_label << "\n";
            // Load the reference of "false" into $a1
            env.os << LA << A1 << " ";
            CgenRef(env.os, false);
            env.os << "\n";
            // Jump to equality test
            // There is some magic going on in equality_test
            emit_equality_test(env.os);
            // Conclude with the merge label
            env.os << "label" << merge_label << LABEL;
    } // end switch

    // Pop the lhs result off the stack
    env.os << ADDIU << SP << " " << SP << " 4\n";
} // end void BinaryOperator::CodeGen(CgenEnv &env)


void Cond::CodeGen(CgenEnv &env) {
    pred_->CodeGen(env);
    // Load the value of the evaluated boolean (at offset 12)
    env.os << LW << T1 << " 12(" << ACC << ")\n";
    // If false, jump to a false label
    int false_label = num_label;
    env.os << BEQZ << T1 << " label" << false_label << "\n";
    num_label++;
    // CodeGen for true
    then_branch_->CodeGen(env);
    // Merge into master flow
    int merge_label = num_label;
    env.os << BRANCH << " label" << merge_label << "\n";
    num_label++;
    // CodeGen for flase
    env.os << "label" << false_label << LABEL;
    else_branch_->CodeGen(env);
    // Conclude with a merge label
    env.os << "label" << merge_label << LABEL;
} // end void Cond::CodeGen(CgenEnv &env)


void Loop::CodeGen(CgenEnv &env) {
    int loop_label = num_label;
    num_label++;
    env.os << "label" << loop_label << LABEL;
    // evaluate predicate
    pred_->CodeGen(env);
    // Load the value of the evaluated boolean (at offset 12)
    env.os << LW << T1 << " 12(" << ACC << ")\n";
    // If false quit loop
    int merge_label = num_label;
    num_label++;
    env.os << BEQZ << T1 << " label" << merge_label << "\n";
    // Loop body
    body_->CodeGen(env);
    // To the next iteration
    env.os << BRANCH << " label" << loop_label << "\n";
    // Conclude with a merge label
    env.os << "label" << merge_label << LABEL;
} // end void Loop::CodeGen(CgenEnv &env)

}  // namespace cool
