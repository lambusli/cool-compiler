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

Copyright 20172-2019 Michael Linderman.

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
 * @brief Types and functions for working with the AST
 *
 * File provides base class for nodes in the inheritance graph, a class table and other helper
 * functions for initialized those data structures with Cool's built-in classes.
 */
#pragma once

#include <cassert>
#include <unordered_map>
#include <vector>

#include "ast.h"

namespace cool {

template <class Node>
class KlassTable;

/**
 * @brief Base class for nodes in the inheritance graph
 *
 * You will need to extend this class to create specific nodes for the inheritance graph used in
 * semantic analysis and code generation
 *
 * @tparam Node
 */
template <class Node>
class InheritanceNode {
 public:
  /**
   * @param klass Klass ASTNode for this inheritance graph node
   * @param inheritable true if class can be a parent class (true for all user-defined classes)
   * @param basic true if basic class, e.g. Bool (false for all user-defined classes)
   * @return
   */
  InheritanceNode(Klass* klass, bool inheritable, bool basic)
      : klass_(klass), inheritable_(inheritable), basic_(basic) {}

  virtual ~InheritanceNode() = default;

  /// Class AST node for this inheritance graph node
  Klass* klass() const { return klass_; }

  /// Name of the associated class
  Symbol* name() const { return klass_->name(); }

  /// File name for the associated class
  StringLiteral* filename() const { return klass_->filename(); }

  /// Get parent node
  Node* parent() const { return parent_; }

  /// Get name of parent class
  Symbol* parent_name() const { return klass_->parent(); }

  /// true if classes inherit from this class
  bool inheritable() const { return inheritable_; }

  /// true if this is a basic (built-in) class
  bool basic() const { return basic_; }

 protected:
  Klass* klass_;
  bool inheritable_;
  bool basic_;

  /// Parent node in the inheritance graph
  Node* parent_ = nullptr;

  /// Child nodes of this class
  std::vector<Node*> children_;

  friend class KlassTable<Node>;
};

/**
 * @brief Base class for Cool class table
 *
 * The KlassTable maps a class name to its InheritanceNode. It can be used to build and query the
 * inheritance graph.
 *
 * @tparam Node Type for nodes in inheritance graph
 */
template <class Node>
class KlassTable {
 public:
  KlassTable() {
    // Install special and built-in classes
    InstallBasicClasses();

    // Sub-class constructors are responsible for building inheritance graph
  }

  /**
   * Get the root of the inheritance graph.
   *
   * By the Cool specification, the root of the inheritance graph must always be Object, thus this
   * root node is automatically set to the Node for the Object class.
   */
  Node* root() const { return root_; }

  /**
   * Find the inheritance node for a class by name
   * @param name Class name
   * @return InheritanceNode or nullptr if class not found
   */
  const Node* ClassFind(Symbol* name) const {
    auto found_node = node_table_.find(name);
    return (found_node != node_table_.end()) ? &(found_node->second) : nullptr;
  }

  Node* ClassFind(Symbol* name) {
    // The casting enables us to avoid duplicating const and non-const methods.
    // Adapted from: https://stackoverflow.com/a/123995
    return const_cast<Node*>(static_cast<const KlassTable&>(*this).ClassFind(name));
  }

 protected:
  /**
   * Root of the inheritance tree
   */
  Node* root_ = nullptr;

  /**
   * Map classes names to InheritanceNodes. Includes "special" classes
   * used by the compiler internally.
   */
  std::unordered_map<Symbol*, Node> node_table_;

  /**
   * Track InheritanceNodes for only classes that can appear in the inheritance graph.
   * Excludes "special" classes used by the compiler internally.
   */
  std::vector<Node*> nodes_;

  /**
   * @brief Install node for special classes used by compiler that are not included in the
   * inheritance graph
   *
   * Add node to name-node map, but not container tracking nodes in the inheritance graph. This
   * method is only used for special classes, like \p No_class, which are not included in the
   * inheritance graph.
   * 
   * @return Node*
   */
  template <class... Args>
  Node* InstallSpecialClass(Args&&... args) {
    Node node(std::forward<Args>(args)...);
    auto added_node = node_table_.emplace(node.name(), std::move(node));
    assert(added_node.second);  // Should have already checked for unique class name
    return &(added_node.first->second);
  }

  /**
   * @brief Install node in inheritance graph into class table
   *
   * This function utilizes "perfect forwarding" to forward its arguments to the
   * constructor for Node as though you had invoked that constructor directly. It
   * expects the same arguments as the Node constructor.
   *
   * @return Node*
   */
  template <class... Args>
  Node* InstallClass(Args&&... args) {
    Node* node = InstallSpecialClass(std::forward<Args>(args)...);
    nodes_.push_back(node);
    return node;
  }

  /**
   * @brief Install Cool built-in classes into class table
   *
   * Alongside installing basic classes, this methods sets the root
   * of the tree to Object class.
   */
  void InstallBasicClasses();

  /**
   * @brief Install user-defined Cool classes into class table.
   *
   * The base implementation assumes that classes form a valid inheritance graph. You could override
   * this method to customize graph construction, e.g. to perform additional validity checks before
   * invoking InstallClass to install a Klass in the graph.
   *
   * @param klasses All Klass AST nodes in the program
   */
  void InstallClasses(Klasses* klasses) {
    for (auto klass : *klasses) {
      InstallClass(klass, true /*Can Inherit*/, false /*NotBasic*/);
    }
  }

};

/**
 * @name Built-in class factories
 */
///@{
// Special classes that are not part of the inheritance
/// No_class serves as the parent of Object and the other special classes
Klass* CreateNoClassKlass();
/// SELF_TYPE is the self class; it cannot be redefined or inherited.
Klass* CreateSELF_TYPEKlass();
/// prim_slot is a class known to the code generator.
Klass* CreatePrimSlotKlass();

// Basic classes
/// Built-in Object class
Klass* CreateObjectKlass();
/// Built-in IO class
Klass* CreateIOKlass();
/// Built-in Int class
Klass* CreateIntKlass();
/// Built-in Bool class
Klass* CreateBoolKlass();
/// Built-in String class
Klass* CreateStringKlass();
///@}

template <class Node>
void KlassTable<Node>::InstallBasicClasses() {
  // Special classes that are installed in the class table but are not part of the inheritance
  // graph:
  // * No_class serves as the parent of Object and the other special classes.
  // * SELF_TYPE is the self class; it cannot be redefined or inherited.
  // * prim_slot is a class known to the code generator.
  InstallSpecialClass(CreateNoClassKlass(), true /* Can Inherit */, true /* Basic */);
  InstallSpecialClass(CreateSELF_TYPEKlass(), false /* Can't Inherit */, true /* Basic */);
  InstallSpecialClass(CreatePrimSlotKlass(), false /* Can't Inherit */, true /* Basic */);

  // Basic classes installed in both the class table and inheritance graph
  // Set Object as root of the graph
  root_ = InstallClass(CreateObjectKlass(), true /*Can Inherit*/, true /*Basic*/);
  InstallClass(CreateIOKlass(), true /*Can Inherit*/, true /*Basic*/);
  InstallClass(CreateIntKlass(), false /*Can't Inherit*/, true /*Basic*/);
  InstallClass(CreateBoolKlass(), false /*Can't Inherit*/, true /*Basic*/);
  InstallClass(CreateStringKlass(), false /*Can't Inherit*/, true /*Basic*/);
}

}  // namespace cool
