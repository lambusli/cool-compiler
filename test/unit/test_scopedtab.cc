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
#include "scopedtab.h"

TEST(SymTabTest, ReturnsMostCloselyNestedScope) {
  // Create string table and test keys (we don't use gIdentTable to prevent crosstalk with
  // other tests)
  cool::SymbolTable<cool::Symbol> string_table;
  cool::Symbol *foo = string_table.emplace("foo"), *bar = string_table.emplace("bar"), *baz = string_table.emplace("baz");

  // Possible values
  int a=1, b=2, c=3;

  cool::ScopedTable<cool::Symbol*,int*> table;

  ASSERT_EQ(nullptr, table.Lookup(foo));

  EXPECT_EQ(&a, table.AddToScope(foo, &a));
  EXPECT_EQ(&b, table.AddToScope(bar, &b));

  table.EnterScope();

  EXPECT_EQ(&c, table.AddToScope(foo, &c));
  EXPECT_EQ(&c, table.Lookup(foo));

  EXPECT_EQ(&b, table.Lookup(bar));
  EXPECT_EQ(nullptr, table.Probe(bar));

  EXPECT_EQ(&a, table.AddToScope(baz, &a));

  table.ExitScope();

  EXPECT_EQ(&a, table.Lookup(foo));
  EXPECT_EQ(&b, table.Lookup(bar));
  EXPECT_EQ(nullptr, table.Lookup(baz));
}

TEST(SymTabTest, CopyConstructsTable) {
  // Create string table and test keys (we don't use gIdentTable to prevent crosstalk with
  // other tests)
  cool::SymbolTable<cool::Symbol> string_table;
  cool::Symbol *foo = string_table.emplace("foo"), *bar = string_table.emplace("bar"), *baz = string_table.emplace("baz");

  // Possible values
  int a=1, b=2, c=3;

  cool::ScopedTable<cool::Symbol*,int*> table1;

  table1.EnterScope();
  table1.AddToScope(foo, &a);
  table1.AddToScope(bar, &b);
  table1.EnterScope();
  table1.AddToScope(baz, &c);

  cool::ScopedTable<cool::Symbol*,int*> table2(table1);
  EXPECT_EQ(&c, table2.Probe(baz));
  EXPECT_EQ(nullptr, table2.Probe(bar));
  table2.ExitScope();
  EXPECT_EQ(&a, table2.Probe(foo));
  EXPECT_EQ(&b, table2.Probe(bar));
}

TEST(SymTabTest, DumpsTable) {
  // Create string table and test keys (we don't use gIdentTable to prevent crosstalk with
  // other tests)
  cool::SymbolTable<cool::Symbol> string_table;
  cool::Symbol *foo = string_table.emplace("foo"), *bar = string_table.emplace("bar"),
               *baz = string_table.emplace("baz");

  // Possible values
  int a = 1, b = 2, c = 3;

  cool::ScopedTable<cool::Symbol *, int*> table1;

  table1.EnterScope();
  table1.AddToScope(foo, &a);
  table1.EnterScope();
  table1.AddToScope(bar, &b);
  table1.AddToScope(baz, &c);

  std::stringstream output;
  output << table1;

  std::string expected(
R"(--------------------
baz: 3
bar: 2
--------------------
foo: 1
--------------------
)");
    EXPECT_EQ(expected, output.str());
}
