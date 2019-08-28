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
#include <sstream>
#include <gtest/gtest.h>
#include "utilities.h"

TEST(UtilityFunctionsTest, EscapesString) {
    std::stringstream ss;
    cool::print_escaped_string(ss, "\\\"\n\t\b\ftest");
    EXPECT_EQ("\\\\\\\"\\n\\t\\b\\ftest", ss.str());
}
