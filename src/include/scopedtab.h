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
 * @brief Scope-aware lookup table useful in semantic analysis and code generation.
 */
#pragma once

#include <stdexcept>
#include <forward_list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <type_traits>

namespace cool {

  /**
   * @brief Scoped table for use as a SymbolTable in AST analysis
   *
   * The table requires that the \p Value type be a pointer type, e.g. a pointer to an ASTNode or a \ref Symbol.
   *
   * Example usage creating a ScopedTable mapping an identifier (as a Symbol*) to a type (also a Symbol*):
   * \code{.cpp}
   * ScopedTable<Symbol*,Symbol*> variable_table;
   * variable_table.EnterScope();
   * variable_tale.AddToScope(name, type);
   * variable_table.Probe(name);  // Should return type
   * \endcode
   *
   * @tparam Key
   * @tparam Value
   */
  template<class Key, class Value>
  class ScopedTable {
    static_assert(std::is_pointer<Value>::value == true,  "ScopedTable Value must be a pointer type");
    typedef std::unordered_map<Key, Value> ScopeEntry;
    typedef std::forward_list<ScopeEntry> ScopeStack;

   public:
    typedef Key key_type;
    typedef Value value_type;

    ScopedTable() = default;

    /**
     * @brief Copy constructor
     * @param Other ScopedTable to copy
     */
    ScopedTable(const ScopedTable& other) = default;

    /// Push new scope onto the stack
    void EnterScope() { scopes_.emplace_front(); }

    /// Pop current scope off the stack
    void ExitScope() {
      if (!scopes_.empty())
        scopes_.pop_front();
    }

    /**
     * @brief Add key and value to current scope on top of the stack
     *
     * Will create new scope if one does not currently exist. Will throw std::invalid_argument
     * if key already exists in scope.
     *
     * @param key Key
     * @param value Associated value
     * @return Value Non-owning pointer to \p value
     */
    Value AddToScope(const Key& key, Value value) {
      if (scopes_.empty()) {
        EnterScope();
      }
      auto r = scopes_.front().emplace(key, value);
      if (!r.second) {
        throw std::invalid_argument("key already exists in scope");
      }
      return r.first->second;
    }

    /**
     * @brief Return value associated key in nearest scope (examining all scopes)
     *
     * @param key Key to lookup
     * @return Value  Non-owning pointer to value or nullptr if not present in any scope
     */
    Value Lookup(const Key& key) const {
      for (auto & scope : scopes_) {
        auto found = scope.find(key);
        if (found != scope.end())
          return found->second;
      }
      return nullptr;
    }

    /**
     * @brief Return value associated key in current scope
     *
     * @param key Key to lookup
     * @return Value Non-owning pointer to value or nullptr if not present in current scope
     */
    Value Probe(const Key& key) const {
      if (!scopes_.empty()) {
        const ScopeEntry& scope = scopes_.front();
        auto found = scope.find(key);
        if (found != scope.end())
          return found->second;
      }
      return nullptr;
    }

    /**
     * @brief Dump scoped to output stream
     *
     * Output is in search order, with scopes separated by dashed lines, e.g.
     * ~~~
     * --------------------
     * key: value found first
     * --------------------
     * key: value found second
     * --------------------
     * ~~~
     *
     * @param os
     * @param s
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const ScopedTable& s) {
      auto seperator = std::string(20, '-');
      os << seperator << std::endl;
      for (const auto& scope : s.scopes_) {
        for (const auto& entry : scope) {
            os << entry.first << ": " << *entry.second << std::endl;
        }
        os << seperator << std::endl;
      }
      return os;
    }

   private:
    ScopeStack scopes_;
  };
}
