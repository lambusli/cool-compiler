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
 * @brief Data structures used in code generation
 */
#include "ast.h"
#include "ast_consumer.h"
#include "emit.h"
#include "scopedtab.h"
#include <assert.h>
#include <stdio.h>

/// Switch for optimizing code generator
extern bool cgen_optimize;

/// Switch to disable register allocator
extern bool disable_reg_alloc;

/**
 * @name Garbage collection options
 * {@}
 */
extern enum Memmgr { GC_NOGC, GC_GENGC, GC_SNCGC } cgen_Memmgr;

extern enum Memmgr_Test { GC_NORMAL, GC_TEST } cgen_Memmgr_Test;

extern enum Memmgr_Debug { GC_QUICK, GC_DEBUG } cgen_Memmgr_Debug;
//@}

namespace cool {

/**
 * Main entry point for code generation
 * @param program Program AST node
 * @param os std::ostream to write generated code to
 */
void Cgen(Program* program, std::ostream& os);

// Forward declarations
class CgenKlassTable;

/**
 * @brief Node in the code generation inheritance graph
 */
class CgenNode : public InheritanceNode<CgenNode> {
 public:
  CgenNode(Klass* klass, bool inheritable, bool basic)
      : InheritanceNode(klass, inheritable, basic), tag_(0) {}

 private:
  /**
   * Unique integer tag for class.
   *
   * As specified in a "A Tour of the Cool Support Code", each class has a unique integer tag. "The
   * runtime system uses the class tag in equality comparisons between objects of the basic classes
   * and in the abort functions to index a table containing the name of each class."
   *
   * During construction this tag is set to 0. You will need to set the tag to a unique value at
   * some point during the initialization of the node. Other than that the tags are unique, there is
   * no specific ordering requirement.
   */
  std::size_t tag_;


  friend class CgenKlassTable;
};

/// Class table for use in code generation
class CgenKlassTable : public KlassTable<CgenNode> {
 public:
  CgenKlassTable(Klasses* klasses);

  /**
   * Find integer tag for a class by name
   * @param name Class name
   * @return tag
   */
  std::size_t TagFind(Symbol* name) const {
    auto node = ClassFind(name);
    assert(node);
    return node->tag_;
  }

  /**
   * @brief Generate code for entire Cool program as represented by this KlassTable.
   *
   * This method would be called by cool::Cgen after you constructed the CgenKlassTable from the Program AST node. 
   *
   * @param os std::ostream to write generated code to
   */
  void CodeGen(std::ostream& os);

 private:

  /**
   * Emit code to the start the .data segment and declare global names
   * @param os std::ostream to write generated code to
   */
  void CgenGlobalData(std::ostream&) const;

  /**
   * Emit code to select the GC mode
   * @param os std::ostream to write generated code to
   */
  void CgenSelectGC(std::ostream& os) const;

  /**
   * Emit constants (literals)
   * @param os std::ostream to write generated code to
   */
  void CgenConstants(std::ostream& os) const;


  /**
   * Emit code to start the .text segment and declare global names
   * @param os std::ostream to write generated code to
   */
  void CgenGlobalText(std::ostream& os) const;

};


}  // namespace cool
