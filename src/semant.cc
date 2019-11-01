
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

    // Pass 1, Part 1: Build inheritance graph
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

        // Create Inheritance graph
        SemantNode *new_node = ClassFind(klass->name());
        SemantNode *parent_of_new_node = ClassFind(klass->parent());
        new_node->parent_ = parent_of_new_node;  // Link from child to parent

    }

    if (error_.errors() > 0) return;  // Can't continue with class table construction if errors found

    // Pass 1, Part 2: Check for cycles in inheritance graph
    // Do some experiment for now

    // Experment 1: print out root of the SemantKlassTable
    std::cout << "The root of this SemantKlassTable is: "
              << root()->name() << std::endl;

    // Traverse std::vector< SemantNode * > nodes_
    for (auto node : nodes_) {
        if (node->parent()) {
            std::cout << "Name: " << node->name()
                      << " Parent: " << node->parent()->name() << std::endl;
        } else {
            std::cout << "Name: " << node->name()
                      << " Parent: " << "NULL" << std::endl;
        }

    }

    // Traverse std::unordered_map< Symbol *, SemantNode > 	node_table_

}


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

}

}  // namespace cool
