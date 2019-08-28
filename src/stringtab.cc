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

#include <cassert>
#include <cstring>
#include <new>
#include <type_traits>

#include "stringtab.h"

namespace cool {
StringRef::StringRef(const char* string)
    : data_(string), length_(string ? ::strlen(string) : 0) {}

StringRef::StringRef(const StringEntry* entry)
    : StringRef(entry->value()) {}

bool StringRef::operator==(const StringRef& rhs) const {
  return length_ == rhs.length_ && ::memcmp(data_, rhs.data_, length_) == 0;
};

// Nifty Counter Idiom
// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Nifty_Counter

static std::size_t gSymbolTableCounter;

#define SYMBOL_TABLE_DECLS(TYPE, VAR, STORE_VAR) \
static typename std::aligned_storage<sizeof(TYPE), alignof(TYPE)>::type STORE_VAR; \
TYPE & VAR = reinterpret_cast<TYPE &>(STORE_VAR);

SYMBOL_TABLE_DECLS(SymbolTable<Symbol>, gIdentTable, gIdentTableStorage);
SYMBOL_TABLE_DECLS(SymbolTable<StringEntry>, gStringTable, gStringTableStorage);
SYMBOL_TABLE_DECLS(SymbolTable<Int32Entry>, gIntTable, gIntTableStorage);

#undef SYMBOL_TABLE_DECLS

SymbolTablesInitializer::SymbolTablesInitializer () {
  if (gSymbolTableCounter++ == 0) {
    new (&gIdentTable) SymbolTable<Symbol>();
    new (&gStringTable) SymbolTable<StringEntry>();
    new (&gIntTable) SymbolTable<Int32Entry>();
  }
}
SymbolTablesInitializer::~SymbolTablesInitializer () {
  if (--gSymbolTableCounter == 0) {
    gIdentTable.~SymbolTable<Symbol>();
    gStringTable.~SymbolTable<StringEntry>();
    gIntTable.~SymbolTable<Int32Entry>();
  }
}
} // namespace cool
