/*
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
#include <gtest/gtest.h>
#include "stringtab.h"

TEST(StringTableTest, MaintainsUniqueIdentifiers) {
  cool::SymbolTable<cool::Symbol> string_table;

  cool::Symbol* sym = string_table.emplace("Object");
  ASSERT_NE(nullptr, sym);
  EXPECT_EQ(sym, string_table.emplace("Object"));
  EXPECT_EQ(0UL, sym->id());

  cool::Symbol* sym2 = string_table.emplace("Int");
  ASSERT_NE(nullptr, sym);
  EXPECT_NE(sym, sym2);
  EXPECT_EQ(1UL, sym2->id());

  std::string str("Int");
  EXPECT_EQ(sym2, string_table.emplace(str));
}

TEST(StringTableTest, DifferentHasMethods) {
  cool::SymbolTable<cool::Symbol> string_table;
  cool::Symbol* sym = string_table.emplace("Object");
  EXPECT_TRUE(string_table.has(sym));
  EXPECT_TRUE(string_table.has("Object"));
}

TEST(StringTableTest, LookupFindsElement) {
  cool::SymbolTable<cool::Symbol> string_table;
  cool::Symbol* sym = string_table.emplace("Object");
  EXPECT_EQ(sym, string_table.lookup("Object"));
  EXPECT_EQ(nullptr, string_table.lookup("Junk"));
}

TEST(StringTableTest, CanEmplaceSymbol) {
  cool::SymbolTable<cool::Symbol> string_table1, string_table2;
  cool::Symbol* sym1_2 = string_table1.emplace("Int");
  cool::Symbol* sym2_1 = string_table2.emplace("Int");
  EXPECT_NE(sym1_2, sym2_1);
  EXPECT_EQ(sym1_2->value(), sym2_1->value());
}
