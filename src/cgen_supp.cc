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


#include <iostream>

#include "cgen_supp.h"

namespace {
int ascii = 0;

void ascii_mode(std::ostream& os) {
  if (!ascii) {
    os << "\t.ascii\t\"";
    ascii = 1;
  }
}

void byte_mode(std::ostream& os) {
  if (ascii) {
    os << "\"\n";
    ascii = 0;
  }
}
}

void cool::emit_string_constant(std::ostream& os, const char* str) {
  ascii = 0;

  while (*str) {
    switch (*str) {
      case '\n':
        ascii_mode(os);
        os << "\\n";
        break;
      case '\t':
        ascii_mode(os);
        os << "\\t";
        break;
      case '\\':
        byte_mode(os);
        os << "\t.byte\t" << (int)((unsigned char)'\\') << std::endl;
        break;
      case '"':
        ascii_mode(os);
        os << "\\\"";
        break;
      default:
        if (*str >= ' ' && ((unsigned char)*str) < 128) {
          ascii_mode(os);
          os << *str;
        } else {
          byte_mode(os);
          os << "\t.byte\t" << (int)((unsigned char)*str) << std::endl;
        }
        break;
    }
    str++;
  }
  byte_mode(os);
  os << "\t.byte\t0\t" << std::endl;
}
