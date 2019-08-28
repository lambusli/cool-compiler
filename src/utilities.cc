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
#include <iomanip>
#include <cassert>
#include <cctype>

#include "cool_parse.h"  // Defines tokens
#include "ast.h"
#include "stringtab.h"
#include "utilities.h"


const char* cool::cool_token_to_string(int tok) {
  switch (tok) {
    case 0:            return("EOF");
    case (CLASS):      return("CLASS");
    case (ELSE):       return("ELSE");
    case (FI):         return("FI");
    case (IF):         return("IF");
    case (IN):         return("IN");
    case (INHERITS):   return("INHERITS");
    case (LET):        return("LET");
    case (LOOP):       return("LOOP");
    case (POOL):       return("POOL");
    case (THEN):       return("THEN");
    case (WHILE):      return("WHILE");
    case (ASSIGN):     return("ASSIGN");
    case (CASE):       return("CASE");
    case (ESAC):       return("ESAC");
    case (OF):         return("OF");
    case (DARROW):     return("DARROW");
    case (NEW):        return("NEW");
    case (STR_CONST):  return("STR_CONST");
    case (INT_CONST):  return("INT_CONST");
    case (BOOL_CONST): return("BOOL_CONST");
    case (TYPEID):     return("TYPEID");
    case (OBJECTID):   return("OBJECTID");
    case (ERROR):      return("ERROR");
    case (LE):         return("LE");
    case (NOT):        return("NOT");
    case (ISVOID):     return("ISVOID");
    case '+': return("'+'");
    case '/': return("'/'");
    case '-': return("'-'");
    case '*': return("'*'");
    case '=': return("'='");
    case '<': return("'<'");
    case '.': return("'.'");
    case '~': return("'~'");
    case ',': return("','");
    case ';': return("';'");
    case ':': return("':'");
    case '(': return("'('");
    case ')': return("')'");
    case '@': return("'@'");
    case '{': return("'{'");
    case '}': return("'}'");
    default:  return("<Invalid Token>");
  }
}

void cool::print_cool_token(std::ostream& out, int tok) {

  out << cool_token_to_string(tok);

  switch (tok) {
    case (STR_CONST):
      out << " = ";
      out << " \"";
      print_escaped_string(out, static_cast<StringLiteral*>(cool_yylval.expression)->value());
      out << "\"";
#ifdef DEBUG
      assert(gStringTable.has(static_cast<StringLiteral*>(cool_yylval.expression)->value()));
#endif
      break;
    case (INT_CONST):
      out << " = " << static_cast<IntLiteral*>(cool_yylval.expression)->value();
#ifdef DEBUG
      assert(gIntTable.has(static_cast<IntLiteral*>(cool_yylval.expression)->value()));
#endif
      break;
    case (BOOL_CONST):
      out << (static_cast<BoolLiteral*>(cool_yylval.expression)->value() ? " = true" : " = false");
      break;
    case (TYPEID):
    case (OBJECTID):
      out << " = " << cool_yylval.symbol;
#ifdef DEBUG
      assert(gIdentTable.has(cool_yylval.symbol));
#endif
      break;
    case (ERROR):
      out << " = ";
      print_escaped_string(out, cool_yylval.error_msg);
      break;
  }
}

void cool::dump_cool_token(std::ostream& out, int lineno, int token, YYSTYPE yylval) {
  out << "#" << lineno << " " << cool_token_to_string(token);

  switch (token) {
    case (STR_CONST):
      out << " \"";
      print_escaped_string(out, static_cast<StringLiteral*>(cool_yylval.expression)->value());
      out << "\"";
#ifdef DEBUG
      assert(gStringTable.has(static_cast<StringLiteral*>(cool_yylval.expression)->value()));
#endif
      break;
    case (INT_CONST):
      out << " " << static_cast<IntLiteral*>(cool_yylval.expression)->value();
#ifdef DEBUG
      assert(gIntTable.has(static_cast<IntLiteral*>(cool_yylval.expression)->value()));
#endif
      break;
    case (BOOL_CONST):
      out << (static_cast<BoolLiteral*>(cool_yylval.expression)->value() ? " true" : " false");
      break;
    case (TYPEID):
    case (OBJECTID):
      out << " " << cool_yylval.symbol;
#ifdef DEBUG
      assert(gIdentTable.has(cool_yylval.symbol));
#endif
      break;
    case (ERROR):
      // As part of assignment 2 students are supposed to
      // *not* coalesce error characters into one string; therefore,
      // if we see an "empty" string here, we can safely assume the
      // lexer is reporting an occurrence of an illegal NUL in the
      // input stream
      if (cool_yylval.error_msg[0] == 0) {
        out << " \"\\000\"";
      }
      else {
        out << " \"";
        print_escaped_string(out, cool_yylval.error_msg);
        out << "\"";
        break;
      }
  }
  out << std::endl;
}
