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

#include "ast.h"
#include <algorithm>
#include <unordered_map>

namespace {
const size_t kIndent = 2;
}

namespace cool {

Program* Program::Create(Klasses* klasses, SourceLoc loc) { return new Program(klasses, loc); }

void Program::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_program" << std::endl;
  for (auto& klass : *klasses_) {
    klass->DumpTree(os, level + kIndent, with_types);
  }
}

Klass* Klass::Create(Symbol* name, Symbol* parent, Features* features, StringLiteral* filename,
                     SourceLoc loc) {
  return new Klass(name, parent, features, filename, loc);
}

Method* Klass::method(Symbol* name) const {
  // And example of using child iterators with algorithms from the STL
  auto found = std::find_if(features_->begin(), features_->end(), [name](Feature* feature) {
    return feature->method() && feature->name() == name;
  });
  return (found != features_->end()) ? dynamic_cast<Method*>(*found) : nullptr;
}

Attr* Klass::attr(Symbol* name) const {
  auto found = std::find_if(features_->begin(), features_->end(), [name](Feature* feature) {
    return feature->attr() && feature->name() == name;
  });
  return (found != features_->end()) ? dynamic_cast<Attr*>(*found) : nullptr;
}

void Klass::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_class" << std::endl;

  level += kIndent;
  pad(os, level) << *name_ << std::endl;
  pad(os, level) << *parent_ << std::endl;

  pad(os, level) << '\"';
  print_escaped_string(os, filename_->value());
  os << '\"' << std::endl;

  pad(os, level) << '(' << std::endl;
  for (auto& feature : *features_) {
    feature->DumpTree(os, level, with_types);
  }
  pad(os, level) << ')' << std::endl;
}

Formal* Formal::Create(Symbol* name, Symbol* decl_type, SourceLoc loc) {
  return new Formal(name, decl_type, loc);
}

void Formal::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_formal" << std::endl;
  level += kIndent;
  pad(os, level) << *name_ << std::endl;
  pad(os, level) << *decl_type_ << std::endl;
}

Method* Method::Create(Symbol* name, Formals* formals, Symbol* decl_type, Expression* body,
                       SourceLoc loc) {
  return new Method(name, formals, decl_type, body, loc);
}

void Method::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_method" << std::endl;
  level += kIndent;
  pad(os, level) << *name_ << std::endl;
  for (auto& formal : *formals_) {
    formal->DumpTree(os, level, with_types);
  }
  pad(os, level) << *decl_type_ << std::endl;
  body_->DumpTree(os, level, with_types);
}

Attr* Attr::Create(Symbol* name, Symbol* decl_type, Expression* init, SourceLoc loc) {
  return new Attr(name, decl_type, init, loc);
}

void Attr::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_attr" << std::endl;
  level += kIndent;
  pad(os, level) << *name_ << std::endl;
  pad(os, level) << *decl_type_ << std::endl;
  init_->DumpTree(os, level, with_types);
}

void Expression::DumpType(std::ostream& os, size_t level, bool with_types) const {
  if (with_types && type_) {
    pad(os, level) << ": " << *type_ << std::endl;
  } else {
    pad(os, level) << ": _no_type" << std::endl;
  }
}

Assign* Assign::Create(Symbol* name, Expression* value, SourceLoc loc) {
  return new Assign(name, value, loc);
}

void Assign::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_assign" << std::endl;
  pad(os, level + kIndent) << *name_ << std::endl;
  value_->DumpTree(os, level + kIndent, with_types);
  DumpType(os, level, with_types);
}

StaticDispatch* StaticDispatch::Create(Expression* receiver, Symbol* dispatch_type, Symbol* name,
                                       Expressions* actuals, SourceLoc loc) {
  return new StaticDispatch(receiver, dispatch_type, name, actuals, loc);
}

void StaticDispatch::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_static_dispatch" << std::endl;
  receiver_->DumpTree(os, level + kIndent, with_types);
  pad(os, level + kIndent) << *dispatch_type_ << std::endl;
  pad(os, level + kIndent) << *name_ << std::endl;
  pad(os, level + kIndent) << '(' << std::endl;
  for (auto& actual : *actuals_) {
    actual->DumpTree(os, level + kIndent, with_types);
  }
  pad(os, level + kIndent) << ')' << std::endl;
  DumpType(os, level, with_types);
}

Dispatch* Dispatch::Create(Expression* receiver, Symbol* name, Expressions* actuals,
                           SourceLoc loc) {
  return new Dispatch(receiver, name, actuals, loc);
}

void Dispatch::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_dispatch" << std::endl;
  receiver_->DumpTree(os, level + kIndent, with_types);
  pad(os, level + kIndent) << *name_ << std::endl;
  pad(os, level + kIndent) << '(' << std::endl;
  for (auto& actual : *actuals_) {
    actual->DumpTree(os, level + kIndent, with_types);
  }
  pad(os, level + kIndent) << ')' << std::endl;
  DumpType(os, level, with_types);
}

Cond* Cond::Create(Expression* pred, Expression* then_branch, Expression* else_branch,
                   SourceLoc loc) {
  return new Cond(pred, then_branch, else_branch, loc);
}

void Cond::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_cond" << std::endl;
  pred_->DumpTree(os, level + kIndent, with_types);
  then_branch_->DumpTree(os, level + kIndent, with_types);
  else_branch_->DumpTree(os, level + kIndent, with_types);
  DumpType(os, level, with_types);
}

Loop* Loop::Create(Expression* pred, Expression* body, SourceLoc loc) {
  return new Loop(pred, body, loc);
}

void Loop::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_loop" << std::endl;
  pred_->DumpTree(os, level + kIndent, with_types);
  body_->DumpTree(os, level + kIndent, with_types);
  DumpType(os, level, with_types);
}

Block* Block::Create(Expressions* body, SourceLoc loc) { return new Block(body, loc); }

void Block::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_block" << std::endl;
  for (auto& expr : *body_) {
    expr->DumpTree(os, level + kIndent, with_types);
  }
  DumpType(os, level, with_types);
}

Let* Let::Create(Symbol* name, Symbol* decl_type, Expression* init, Expression* body,
                 SourceLoc loc) {
  return new Let(name, decl_type, init, body, loc);
}

void Let::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_let" << std::endl;
  pad(os, level + kIndent) << *name_ << std::endl;
  pad(os, level + kIndent) << *decl_type_ << std::endl;
  init_->DumpTree(os, level + kIndent, with_types);
  body_->DumpTree(os, level + kIndent, with_types);
  DumpType(os, level, with_types);
}

Kase* Kase::Create(Expression* input, KaseBranches* cases, SourceLoc loc) {
  return new Kase(input, cases, loc);
}

void Kase::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_typcase" << std::endl;
  input_->DumpTree(os, level + kIndent, with_types);
  for (auto& branch : *cases_) {
    branch->DumpTree(os, level + kIndent, with_types);
  }
  DumpType(os, level, with_types);
}

KaseBranch* KaseBranch::Create(Symbol* name, Symbol* decl_type, Expression* body, SourceLoc loc) {
  return new KaseBranch(name, decl_type, body, loc);
}

void KaseBranch::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_branch" << std::endl;
  pad(os, level + kIndent) << *name_ << std::endl;
  pad(os, level + kIndent) << *decl_type_ << std::endl;
  body_->DumpTree(os, level + kIndent, with_types);
  // We don't dump types of individual case branches
}

Knew* Knew::Create(Symbol* name, SourceLoc loc) { return new Knew(name, loc); }

void Knew::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_new" << std::endl;
  pad(os, level + kIndent) << *name_ << std::endl;
  DumpType(os, level, with_types);
}

namespace {
constexpr const char* DumpOperator(UnaryOperator::UnaryKind kind) {
  switch (kind) {
    case UnaryOperator::UnaryKind::UO_Neg:
      return "_neg";
    case UnaryOperator::UnaryKind::UO_Not:
      return "_comp";
    case UnaryOperator::UnaryKind::UO_IsVoid:
      return "_isvoid";
    default:
      // Silence GCC compiler warnings
      return "";
  }
}

constexpr const char* DumpOperator(BinaryOperator::BinaryKind kind) {
  switch (kind) {
    case BinaryOperator::BinaryKind::BO_Add:
      return "_plus";
    case BinaryOperator::BinaryKind::BO_Sub:
      return "_sub";
    case BinaryOperator::BinaryKind::BO_Mul:
      return "_mul";
    case BinaryOperator::BinaryKind::BO_Div:
      return "_divide";
    case BinaryOperator::BinaryKind::BO_LT:
      return "_lt";
    case BinaryOperator::BinaryKind::BO_EQ:
      return "_eq";
    case BinaryOperator::BinaryKind::BO_LE:
      return "_leq";
    default:
      // Silence GCC compiler warnings
      return "";
  }
}
}  // anonymous namespace

UnaryOperator* UnaryOperator::Create(UnaryKind kind, Expression* input, SourceLoc loc) {
  return new UnaryOperator(kind, input, loc);
}

void UnaryOperator::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << DumpOperator(kind_) << std::endl;
  input_->DumpTree(os, level + kIndent, with_types);
  DumpType(os, level, with_types);
}

const char* BinaryOperator::KindAsString() const {
  switch (kind_) {
    case BinaryKind::BO_Add:
      return "+";
    case BinaryKind::BO_Sub:
      return "-";
    case BinaryKind::BO_Mul:
      return "*";
    case BinaryKind::BO_Div:
      return "/";
    case BinaryKind::BO_LT:
      return "<";
    case BinaryKind::BO_EQ:
      return "=";
    case BinaryKind::BO_LE:
      return "<=";
    default:
      // Silence GCC compiler warnings
      return "";
  }
}

BinaryOperator* BinaryOperator::Create(BinaryKind kind, Expression* lhs, Expression* rhs,
                                       SourceLoc loc) {
  return new BinaryOperator(kind, lhs, rhs, loc);
}

void BinaryOperator::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << DumpOperator(kind_) << std::endl;
  lhs_->DumpTree(os, level + kIndent, with_types);
  rhs_->DumpTree(os, level + kIndent, with_types);
  DumpType(os, level, with_types);
}

Ref* Ref::Create(Symbol* name, SourceLoc loc) { return new Ref(name, loc); }

void Ref::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_object" << std::endl;
  pad(os, level + kIndent) << *name_ << std::endl;
  DumpType(os, level, with_types);
}

NoExpr* NoExpr::Create(SourceLoc loc) { return new NoExpr(loc); }

void NoExpr::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_no_expr" << std::endl;
  DumpType(os, level, with_types);
}

StringLiteral* StringLiteral::Create(const StringEntry* value, SourceLoc loc) {
  return new StringLiteral(value, loc);
}

StringLiteral* StringLiteral::Create(const std::string& string, SourceLoc loc) {
  return Create(gStringTable.emplace(string), loc);
}

StringLiteral* StringLiteral::Create(const char* string, std::size_t length, SourceLoc loc) {
  return Create(gStringTable.emplace(string, length), loc);
}

void StringLiteral::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_string" << std::endl;
  pad(os, level + kIndent) << '\"';
  print_escaped_string(os, value());
  os << '\"' << std::endl;
  DumpType(os, level, with_types);
}

IntLiteral* IntLiteral::Create(const Int32Entry* value, SourceLoc loc) {
  return new IntLiteral(value, loc);
}

IntLiteral* IntLiteral::Create(int32_t value, SourceLoc loc) {
  return Create(gIntTable.emplace(value), loc);
}

void IntLiteral::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_int" << std::endl;
  pad(os, level + kIndent) << value() << std::endl;
  DumpType(os, level, with_types);
}

BoolLiteral* BoolLiteral::Create(bool value, SourceLoc loc) { return new BoolLiteral(value, loc); }

void BoolLiteral::DumpTree(std::ostream& os, size_t level, bool with_types) const {
  DumpLine(os, level);
  pad(os, level) << "_bool" << std::endl;
  pad(os, level + kIndent) << value() << std::endl;
  DumpType(os, level, with_types);
}

}  // namespace cool
