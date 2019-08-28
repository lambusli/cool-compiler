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

#ifndef YY_COOL_YY_HOME_MLINDERMAN_COURSES_CS433_MIDD_COOL_RELEASE_SRC_COOL_PARSER_HPP_INCLUDED
# define YY_COOL_YY_HOME_MLINDERMAN_COURSES_CS433_MIDD_COOL_RELEASE_SRC_COOL_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int cool_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    INHERITS = 259,
    IF = 260,
    THEN = 261,
    ELSE = 262,
    FI = 263,
    IN = 264,
    LET = 265,
    WHILE = 266,
    LOOP = 267,
    POOL = 268,
    CASE = 269,
    ESAC = 270,
    OF = 271,
    DARROW = 272,
    NEW = 273,
    ISVOID = 274,
    ASSIGN = 275,
    NOT = 276,
    LE = 277,
    STR_CONST = 278,
    INT_CONST = 279,
    BOOL_CONST = 280,
    TYPEID = 281,
    OBJECTID = 282,
    ERROR = 283,
    LET_STMT = 284
  };
#endif
/* Tokens.  */
#define CLASS 258
#define INHERITS 259
#define IF 260
#define THEN 261
#define ELSE 262
#define FI 263
#define IN 264
#define LET 265
#define WHILE 266
#define LOOP 267
#define POOL 268
#define CASE 269
#define ESAC 270
#define OF 271
#define DARROW 272
#define NEW 273
#define ISVOID 274
#define ASSIGN 275
#define NOT 276
#define LE 277
#define STR_CONST 278
#define INT_CONST 279
#define BOOL_CONST 280
#define TYPEID 281
#define OBJECTID 282
#define ERROR 283
#define LET_STMT 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 67 "cool.y" /* yacc.c:1909  */

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
  const char *error_msg;

#line 128 "/home/mlinderman/courses/cs433/midd-cool-Release/src/cool-parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE cool_yylval;
extern YYLTYPE cool_yylloc;
int cool_yyparse (void);

#endif /* !YY_COOL_YY_HOME_MLINDERMAN_COURSES_CS433_MIDD_COOL_RELEASE_SRC_COOL_PARSER_HPP_INCLUDED  */
