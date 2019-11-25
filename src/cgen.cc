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
        os << WORD << node->etable_attr_.size() + 3 << std::endl;

        // Dispatch pointer, offset 8
        os << WORD;
        emit_disptable_ref(node->name(), os);
        os << std::endl;

        // Attributes, offset 12+
        for (auto attr_name : node->evector_attr_) {
            os << WORD;
            auto entry = node->etable_attr_[attr_name];

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
        node->etable_attr_ = parent->etable_attr_;
        node->evector_attr_ = parent->evector_attr_;
        node->etable_meth_ = parent->etable_meth_;
        node->evector_meth_ = parent->evector_meth_;
        attr_offset += 4 * node->etable_attr_.size();
        meth_offset += 4 * node->etable_meth_.size();
    }

    // traverse each feature of this CgenNode
    for (auto feature : *node->klass()->features()) {
        if (feature->attr())
        // operation if feature is attribute
        {
            node->evector_attr_.push_back(feature->name());

            AttrBinding *ab = new AttrBinding();
            ab->offset_ = attr_offset;
            ab->class_name_ = node->name();
            ab->attr_name_ = feature->name();
            ab->decl_type_ = feature->decl_type();

            attr_offset += 4;
            node->etable_attr_[feature->name()] = ab;

        } else
        // operation if feature is method
        {
            MethBinding *mb = new MethBinding();
            mb->class_name_ = node->name();
            mb->meth_name_ = feature->name();
            mb->decl_type_ = feature->decl_type();

            // only insert meth_name into vector and bind a new offset
            // if the method was not defined in a parent class
            if (node->etable_meth_[feature->name()] == NULL) {
                node->evector_meth_.push_back(feature->name());
                mb->offset_ = meth_offset;
                meth_offset += 4;
            }
            // if a method is redefined, the offset does not change
            else {
                mb->offset_ = node->etable_meth_[feature->name()]->offset_;
            }

            // Bind
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
            attr->init()->CodeGen(envnow);
        }

        epilogue_init(os); // callee epilogue
    } // end for
} // end CgenKlassTable::CgenObjInit(std::ostream &os) const


// Code generation for all class attributes and methods
void CgenKlassTable::CgenMethBody(std::ostream &os) {
    for (auto node : nodes_) {
        // Create Cgen environment for a specific class
        CgenEnv envnow(this, node, os);

        for (auto feature : *node->klass()->features()) {
            // Generate code only for method bodies
            // Do nothing for an attribute
            if (feature->attr()) {continue; }

            Method *meth = (Method *)feature;
            os << node->name() << "." << meth->name() << LABEL;

        } // end for feature
    } // end for node
} // end CgenKlassTable::CgenMethBody(std::ostream &os) const

void NoExpr::CodeGen(CgenEnv &env) {}

void IntLiteral::CodeGen(CgenEnv &env) {
    env.os << "\t# I am an integer.\n";
}

}  // namespace cool
