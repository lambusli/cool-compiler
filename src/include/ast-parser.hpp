/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_AST_YY_HOME_MLINDERMAN_COURSES_CS433_MIDD_COOL_RELEASE_SRC_AST_PARSER_HPP_INCLUDED
# define YY_AST_YY_HOME_MLINDERMAN_COURSES_CS433_MIDD_COOL_RELEASE_SRC_AST_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int ast_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    CLASS = 259,
    METHOD = 260,
    ATTR = 261,
    FORMAL = 262,
    BRANCH = 263,
    ASSIGN = 264,
    STATIC_DISPATCH = 265,
    DISPATCH = 266,
    COND = 267,
    LOOP = 268,
    TYPCASE = 269,
    BLOCK = 270,
    LET = 271,
    PLUS = 272,
    SUB = 273,
    MUL = 274,
    DIVIDE = 275,
    NEG = 276,
    LT = 277,
    EQ = 278,
    LEQ = 279,
    COMP = 280,
    INT = 281,
    STR = 282,
    BOOL = 283,
    NEW = 284,
    ISVOID = 285,
    NO_EXPR = 286,
    OBJECT = 287,
    NO_TYPE = 288,
    STR_CONST = 289,
    INT_CONST = 290,
    ID = 291,
    LINENO = 292
  };
#endif
/* Tokens.  */
#define PROGRAM 258
#define CLASS 259
#define METHOD 260
#define ATTR 261
#define FORMAL 262
#define BRANCH 263
#define ASSIGN 264
#define STATIC_DISPATCH 265
#define DISPATCH 266
#define COND 267
#define LOOP 268
#define TYPCASE 269
#define BLOCK 270
#define LET 271
#define PLUS 272
#define SUB 273
#define MUL 274
#define DIVIDE 275
#define NEG 276
#define LT 277
#define EQ 278
#define LEQ 279
#define COMP 280
#define INT 281
#define STR 282
#define BOOL 283
#define NEW 284
#define ISVOID 285
#define NO_EXPR 286
#define OBJECT 287
#define NO_TYPE 288
#define STR_CONST 289
#define INT_CONST 290
#define ID 291
#define LINENO 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 60 "ast.y" /* yacc.c:1909  */

  cool::Program* program;
  cool::Klass* klass;
  cool::Klasses* klasses;
  cool::Feature* feature;
  cool::Features* features;
  cool::Formal* formal;
  cool::Formals* formals;
  cool::Expression* expression;
  cool::Expressions* expressions;
  cool::KaseBranch* kase_branch;
  cool::KaseBranches* kase_branches;
  cool::Symbol* symbol;
  cool::StringLiteral* string_literal;
  int lineno;

#line 145 "/home/mlinderman/courses/cs433/midd-cool-Release/src/ast-parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE ast_yylval;

int ast_yyparse (void);

#endif /* !YY_AST_YY_HOME_MLINDERMAN_COURSES_CS433_MIDD_COOL_RELEASE_SRC_AST_PARSER_HPP_INCLUDED  */
