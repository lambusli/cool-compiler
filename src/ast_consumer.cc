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

#include "ast_consumer.h"
#include "ast.h"
#include "stringtab.h"

namespace cool {

/**
 * @name Predefined symbols used in Cool
 *
 * Initialize pre-defined symbols automatically (relying on nifty counter idiom to ensure
 * gIdentTable is created)
 *
 * @{
 */
// clang-format off
Symbol
  *arg = gIdentTable.emplace("arg"),
  *arg2 = gIdentTable.emplace("arg2"),
  *Bool = gIdentTable.emplace("Bool"),
  *concat = gIdentTable.emplace("concat"),
  *cool_abort = gIdentTable.emplace("abort"),
  *copy = gIdentTable.emplace("copy"),
  *Int = gIdentTable.emplace("Int"),
  *in_int = gIdentTable.emplace("in_int"),
  *in_string = gIdentTable.emplace("in_string"),
  *IO = gIdentTable.emplace("IO"),
  *isProto = gIdentTable.emplace("isProto"),
  *length = gIdentTable.emplace("length"),
  *Main = gIdentTable.emplace("Main"),
  *main_meth = gIdentTable.emplace("main"),
  *No_class = gIdentTable.emplace("_no_class"),  // Can't be the name of any user-defined class.
  *No_type = gIdentTable.emplace("_no_type"),
  *Object = gIdentTable.emplace("Object"),
  *out_int = gIdentTable.emplace("out_int"),
  *out_string = gIdentTable.emplace("out_string"),
  *prim_slot = gIdentTable.emplace("_prim_slot"),
  *self = gIdentTable.emplace("self"),
  *SELF_TYPE = gIdentTable.emplace("SELF_TYPE"),
  *String = gIdentTable.emplace("String"),
  *str_field = gIdentTable.emplace("_str_field"),
  *substr = gIdentTable.emplace("substr"),
  *type_name = gIdentTable.emplace("type_name"),
  *val = gIdentTable.emplace("_val");
// clang-format on
// @}

Klass* CreateNoClassKlass() {
  return Klass::Create(No_class, No_class, Features::Create(),
                       StringLiteral::Create("<basic class>"));
}

Klass* CreateSELF_TYPEKlass() {
  return Klass::Create(SELF_TYPE, No_class, Features::Create(),
                       StringLiteral::Create("<basic class>"));
}

Klass* CreatePrimSlotKlass() {
  return Klass::Create(prim_slot, No_class, Features::Create(),
                       StringLiteral::Create("<basic class>"));
}

Klass* CreateObjectKlass() {
  // class Object inherits _no_class {
  //  abort() : Object : SELF_TYPE {...}
  //  type_name() : String : SELF_TYPE {...}
  //  copy() : SELF_TYPE {...}
  // };
  // clang-format off
  return Klass::Create(Object, No_class, Features::Create({
      Method::Create(cool_abort, Formals::Create(), Object, NoExpr::Create()),
      Method::Create(type_name, Formals::Create(), String, NoExpr::Create()),
      Method::Create(copy, Formals::Create(), SELF_TYPE, NoExpr::Create())
  }), StringLiteral::Create("<basic class>"));
  // clang-format on
}

Klass* CreateIOKlass() {
  // class IO inherits Object {
  //  out_string(x : String) : SELF_TYPE {...}
  //  out_int(x : Int) : SELF_TYPE {...}
  //  in_string() : String {...}
  //  in_int() : Int {...}
  // };
  // clang-format off
  return  Klass::Create(IO, Object, Features::Create({
      Method::Create(out_string, Formals::Create(Formal::Create(arg, String)), SELF_TYPE, NoExpr::Create()),
      Method::Create(out_int, Formals::Create(Formal::Create(arg, Int)), SELF_TYPE, NoExpr::Create()),
      Method::Create(in_string, Formals::Create(), String, NoExpr::Create()),
      Method::Create(in_int, Formals::Create(), Int, NoExpr::Create())
  }), StringLiteral::Create("<basic class>"));
  // clang-format on
}

Klass* CreateIntKlass() {
  // class Int inherits Object {
  //  val : prim_slot
  // };
  // clang-format off
  return Klass::Create(Int, Object, Features::Create(
      Attr::Create(val, prim_slot, NoExpr::Create())
  ), StringLiteral::Create("<basic class>"));
  // clang-format on
}

Klass* CreateBoolKlass() {
  // class Bool inherits Object {
  //  val : prim_slot
  // };
  //
  // clang-format off
  return Klass::Create(Bool, Object, Features::Create(
      Attr::Create(val, prim_slot, NoExpr::Create())
  ), StringLiteral::Create("<basic class>"));
  // clang-format on
}

Klass* CreateStringKlass() {
  // class String inherits Object {
  //  val : Int (* Length of the string *)
  //  str_field : prim_slot (* The string itself *)
  //  length() : Int
  //  concat(s : String) : String
  //  substr(i : Int, l : Int) : String
  // };
  //
  // clang-format off
  return Klass::Create(String, Object, Features::Create({
      Attr::Create(val, Int, NoExpr::Create()),
      Attr::Create(str_field, prim_slot, NoExpr::Create()),
      Method::Create(length, Formals::Create(), Int, NoExpr::Create()),
      Method::Create(concat, Formals::Create(Formal::Create(arg, String)), String, NoExpr::Create()),
      Method::Create(substr, Formals::Create({Formal::Create(arg, Int), Formal::Create(arg2, Int)}), String, NoExpr::Create())
  }), StringLiteral::Create("<basic class>"));
  // clang-format on
}

}  // namespace cool
