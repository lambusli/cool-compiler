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
#include "ast.h"

// Symbols defined in ast_consumer.cc
namespace cool {
    extern Symbol* arg;
}

TEST(gStringTableTest, MaintainsStringEntries) {
  using namespace cool;

  StringLiteral* lit = StringLiteral::Create("test string");
  ASSERT_NE(nullptr, lit);
  EXPECT_TRUE(gStringTable.has("test string"));
}

TEST(gIntTableTest, MaintainsIntEntries) {
  using namespace cool;

  IntLiteral* lit = IntLiteral::Create(3);
  ASSERT_NE(nullptr, lit);
  EXPECT_TRUE(gIntTable.has(3));
}

TEST(gIdentTableTest, InitializesPredefinedSymbols) {
    using namespace cool;
    ASSERT_TRUE(arg);
    EXPECT_TRUE(gIdentTable.has("arg"));
}
