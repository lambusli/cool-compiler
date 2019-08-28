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
 * @brief Utility functions for use in the Cool compiler
 */
#pragma once

#include <iostream>
#include <iomanip>
#include <iterator>

union YYSTYPE;

namespace cool {

/// Print escaped string to std::ostream
inline void print_escaped_string(std::ostream& str, const std::string& s) {
  // Include in header to avoid pulling in lexing/parsing libraries
  for (auto& c : s) {
    switch (c) {
      case '\\':
        str << "\\\\";
        break;
      case '\"':
        str << "\\\"";
        break;
      case '\n':
        str << "\\n";
        break;
      case '\t':
        str << "\\t";
        break;
      case '\b':
        str << "\\b";
        break;
      case '\f':
        str << "\\f";
        break;
      default:
        if (isprint(c))
          str << c;
        else {
          // Unprintable characters are printed using octal equivalents.
          // To get the sign of the octal number correct, the character
          // must be cast to an unsigned char before converting it to an
          // integer.
          str << '\\' << std::oct << std::setfill('0') << std::setw(3) << (int)((unsigned char)(c))
              << std::dec << std::setfill(' ');
        }
        break;
    }
  }
}

const char* cool_token_to_string(int tok);
void print_cool_token(std::ostream& out, int tok);
void dump_cool_token(std::ostream& out, int lineno, int token, YYSTYPE yylval);

// Include in header to avoid pulling in lexing/parsing libraries
inline std::ostream& pad(std::ostream& out, int padding) {
  if (padding > 80)
    padding = 80;
  else if (padding < 0)
    return out;
  std::fill_n(std::ostream_iterator<char>(out), padding, ' ');
  return out;
}

} // namespace cool
