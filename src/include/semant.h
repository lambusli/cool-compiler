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
/**
 * @file
 *
 * @brief Data structures used in semantic analysis
 *
 * Define your semantic environment and any other classes needed for semantic analysis here.
 */
#pragma once

#include <assert.h>

#include "ast.h"
#include "ast_consumer.h"
#include "scopedtab.h"
#include "stringtab.h"

#define UNVISITED 0
#define VISITING 1
#define VISITED 2

namespace cool {

/**
 * @brief Main entry point for semantic analysis
 *
 * There are three passes:
 * -# Pass 1: This is not a true pass, as only the classes are inspected. Build the inheritance
 * graph and check for errors. There are two "sub"-passes: check that classes are not redefined and
 * inherit only from defined classes, and check for cycles in the inheritance graph. Compilation is
 * halted if an error is detected between the sub-passes.
 *  -# Pass 2: Build symbol tables for each class. This step is done separately because methods and
 * attributes have global scope; therefore, bindings for all methods and attributes must be known
 * before type checking can be done.
 *  -# Pass 3: Traverse the inheritance graph (which is known to be a tree if there are no cycles),
 * starting from the root class Object. For each class, typecheck each attribute and method.
 * Simultaneously, check identifiers for correct definition/use and for multiple definitions.
 * All parents of a class are checked before a class is checked.
 *
 * @param program Root of the AST
 */
void Semant(Program* program);


// Forward declarations
class SemantNode;
class SemantKlassTable;
// Forward declare your semantic environment here if referenced in SemanticNode or SemanticKlassTable

/**
 * @brief Error tracking and structured printing of semantic errors.
 *
 * Use the most specific error reporting operator possible to generate the most informative error
 * messages.
 *
 * An example of using the error reporting to report "An error with name [symbol]":
 * \code{.cpp}
 * SemantError error(std::cerr);
 * Symbol* name = ...;
 * error() << "An error with identifier " << name << std::endl;
 * \endcode
 */
class SemantError {
 public:
  SemantError(std::ostream& os) : os_(os), errors_(0) {}

  /**
   * @brief Number of errors reported
   *
   * @return std::size_t Number of errors reported
   */
  std::size_t errors() const { return errors_; }

  /**
   * @name Error reporting operators
   *
   * Arguments enable more specific error messages referencing specific files, classes, etc.
   *
   * @return std::ostream& Error reporting stream
   * @{
   */
  std::ostream& operator()(const SemantNode* node);

  /**
   * @brief Report error associated with a specific Cool class.
   *
   * @param klass Class in which error occurred
   */
  std::ostream& operator()(const Klass* klass) { return (*this)(klass->filename(), klass); }

  /**
   * @brief Report error associated with a specific ASTNode in a specific Cool class.
   *
   * @param klass Class in which error occurred
   * @param node AST node with error
   */
  std::ostream& operator()(const Klass* klass, const ASTNode* node) {
    return (*this)(klass->filename(), node);
  }

  /**
   * @brief Report error associated with a specific ASTNode in a specific file.
   *
   * @param filename File name
   * @param node AST node with error
   */
  std::ostream& operator()(const StringLiteral* filename, const ASTNode* node) {
    errors_++;
    os_ << filename << ":" << node->loc() << ": ";
    return os_;
  }

  /// Report generic error (without specific node, etc.)
  std::ostream& operator()() {
    errors_++;
    return os_;
  }
  // @}

 private:
  std::ostream& os_;
  std::size_t errors_;
};


/**
 * @brief InheritanceNode extended for semantic analysis.
 *
 * Uses the Curiously Recurring Template Pattern to enable use of
 * child class types in the parent class.
 */
class SemantNode : public InheritanceNode<SemantNode> {
    public:
        SemantNode(Klass* klass, bool inheritable, bool basic)
          : InheritanceNode(klass, inheritable, basic) {}


    private:
        friend class SemantKlassTable;
        friend void Semant(Program* program);
        int track_visit_ = UNVISITED; // {UNVISITED, VISITING, VISITED}
        ScopedTable<Symbol *, Method *> mtable_; // method-scoped-table of the klass represented by this SemantNode. Storing all the methods defined in this klass.
        ScopedTable<Symbol *, Symbol *> otable_; // object-scoped-table of the klass represented by this SemantNode. Storing all the attributes defined in this klass.
};

/// Class table for use in semantic analysis
class SemantKlassTable : public KlassTable<SemantNode> {
    public:
        /**
        * @brief Construct a new Semant Klass Table object
        *
        * @param error Error reporter
        * @param klasses Class AST nodes in Cool program
        */
        SemantKlassTable(SemantError& error, Klasses* klasses);
        void traverse(SemantNode *klass_node);
        void make_all_sctables(SemantNode *klass_node);


    private:
        /// Semantic error reporting class
        SemantError& error_;

};

// Implement your semantic environment here
class SemantEnv {
  public:
    SemantKlassTable &klass_table;
    SemantNode *curr_semant_node;
    SemantError &error_env;

    SemantEnv(SemantKlassTable &klass_table_arg,
              SemantNode *curr_semant_node_arg, SemantError &error_env_arg);

    void tra();

};




}  // namespace cool
