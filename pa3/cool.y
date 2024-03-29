/*
 * Parser definition for the COOL language.
 */

%{
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
    #include "stringtab.h"
    #include "utilities.h"

    // Locations
    #define YYLTYPE cool::SourceLoc   // The type of locations
    #define cool_yylloc gCurrLineNo   // Use the gCurrLineNo from the lexer for the location of tokens

    // The default action for locations. Use the location of the first
    // terminal/non-terminal.
    #define YYLLOC_DEFAULT(Cur, Rhs, N)         \
        (Cur) = (N) ? YYRHSLOC(Rhs, 1) : YYRHSLOC(Rhs, 0);

    extern const char *gCurrFilename; // Current file being parsed

    void yyerror(const char *s);  // Called for each parse error
    extern int yylex();           // Entry point to the lexer/

    cool::Program* gASTRoot;	    // The result of the parsing
    int omerrs = 0;               // Number of lexing or parsing errors

    using BinaryKind = cool::BinaryOperator::BinaryKind;
    using UnaryKind  = cool::UnaryOperator::UnaryKind;
%}


/* A union of all the types that can be the result of parsing actions. */
%union {
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
}

/*
Declare the terminals; a few have types for associated lexemes.
The token ERROR is never used in the parser; thus, it is a parse
error when the lexer returns it.
 */

%token CLASS 258
%token INHERITS 259
%token IF 260
%token THEN 261
%token ELSE 262
%token FI 263
%token IN 264
%token LET 265
%token WHILE 266
%token LOOP 267
%token POOL 268
%token CASE 269
%token ESAC 270
%token OF 271
%token DARROW 272
%token NEW 273
%token ISVOID 274
%token ASSIGN 275
%token NOT 276
%token LE 277
%token <expression> STR_CONST 278
%token <expression> INT_CONST 279
%token <expression> BOOL_CONST 280
%token <symbol> TYPEID 281
%token <symbol> OBJECTID 282
%token ERROR 283
%token LET_STMT 284

/* The terminal symbol error is reserved for error recovery. */

/* Don't change anything above this line, or your parser will NOT work */
/* --------------------------------------------------------------------*/

/* Declare types for the grammar's non-terminals. */
%type <program> program
%type <klasses> class_list
%type <klass> class
%type <features> optional_feature_list
%type <features> feature_list
%type <feature> feature
%type <expressions> expr_list
%type <expressions> expr_list_2
%type <expressions> expr_list_2_pr
%type <expression> expr
%type <expression> let_list         /* Let me pretend I understand why */
%type <expression> optinit
%type <kase_branches> kase_list     /* Is this correct? */
%type <kase_branch> kase            /* Is this correct? */
%type <formals> formal_list
%type <formals> formal_list_pr
%type <formal> formal


/* Precedence declarations (in reverse order of precedence). */
%right ASSIGN
%precedence NOT
%precedence '='
%precedence '<'
%precedence LE
%left '-'
%left '+'
%left '/'
%left '*'
%precedence ISVOID
%precedence '~'
%precedence '@'
%precedence '.'
%%

program	:
    class_list {
        /* Ensure bison computes location information */
        @$ = @1;
        gASTRoot = cool::Program::Create($1, @1); // Save AST root in a global variable for access by programs
    }
    | error { gASTRoot = cool::Program::Create(cool::Klasses::Create()); }
    ;

/*
* Some clarifications
* $$, $1, $2... is related to syntax directed translation and S-attributed grammar
* The dependency graph flows from bottom to up
* Each nonterminal has a type
* klasses is is an instance of cool::Klasses
*/

class_list :
    class
        // Using the factory method to create a class with just one entry
        { $$ = cool::Klasses::Create($1); }
    | error ';'
        // Error in the 1st class. Create an empty class
        { $$ = cool::Klasses::Create(); }
    | class_list class
        // We got a non-terminal here. Combine them into a new vector
        { $$ = ($1)->push_back($2); }
    | class_list error ';'  { $$ = $1; }
    ;


class :
    CLASS TYPEID '{' optional_feature_list '}' ';'
    {
        /* If no parent class is specified, the class inherits from Object */
        $$ = cool::Klass::Create($2, cool::gIdentTable.emplace("Object"), $4, cool::StringLiteral::Create(gCurrFilename), @1);
    }
    | CLASS TYPEID INHERITS TYPEID '{' optional_feature_list '}' ';'
    {
        $$ = cool::Klass::Create($2, $4, $6, cool::StringLiteral::Create(gCurrFilename), @1);
    }
    ;

/* Feature list may be empty, but no empty features in list. You will need to flesh this out further. */
optional_feature_list :
    /* empty */ { $$ = cool::Features::Create(); }
    | feature_list {$$ = $1;}
    ;


feature_list:
    feature ';'  {$$ = cool::Features::Create($1);}
    | error ';' {$$ = cool::Features::Create();}
    | feature_list feature ';'  {$$ = ($1)->push_back($2);}
    | feature_list error ';' {$$ = $1;}
    ;


feature :
    OBJECTID ':' TYPEID  {
        $$ = cool::Attr::Create($1, $3, cool::NoExpr::Create(), @1);
    }
    | OBJECTID ':' TYPEID ASSIGN expr  {
        $$ = cool::Attr::Create($1, $3, $5, @1);
    }
    | OBJECTID '(' formal_list ')' ':' TYPEID '{' expr '}'
    {
        $$ = cool::Method::Create($1, $3, $6, $8, @1);
    }
    ;

expr :
    BOOL_CONST      {$$ = $1;}
    | STR_CONST     {$$ = $1;}
    | INT_CONST     {$$ = $1;}
    | OBJECTID      {$$ = cool::Ref::Create($1, @1);}
    | NEW TYPEID    {$$ = cool::Knew::Create($2, @1);}
    | CASE expr OF kase_list ESAC  {$$ = cool::Kase::Create($2, $4, @1);}
    | LET let_list  {$$ = $2;}
    | '{' expr_list  '}' {$$ = cool::Block::Create($2, @1);}
    | WHILE expr LOOP expr POOL {$$ = cool::Loop::Create($2, $4, @1); }
    | IF expr THEN expr ELSE expr FI  {$$ = cool::Cond::Create($2, $4, $6, @1);}
    | OBJECTID '(' expr_list_2 ')'
    { $$ = cool::Dispatch::Create(cool::Ref::Create(
                                    cool::gIdentTable.emplace("self"), @1
                                  ), $1, $3, @1);
    }
    /* Operator precedence */
    | '(' expr ')'  {$$ = $2;}
    | expr '.' OBJECTID '(' expr_list_2 ')' { $$ = cool::Dispatch::Create($1, $3, $5, @1); }
    | expr '@' TYPEID '.' OBJECTID '(' expr_list_2 ')'
    {
        $$ = cool::StaticDispatch::Create($1, $3, $5, $7, @1);
    }
    | '~' expr      {$$ = cool::UnaryOperator::Create(UnaryKind::UO_Neg, $2, @1);}
    | ISVOID expr   {$$ = cool::UnaryOperator::Create(UnaryKind::UO_IsVoid, $2, @1);}
    | expr '*' expr {$$ = cool::BinaryOperator::Create(BinaryKind::BO_Mul, $1, $3, @1);}
    | expr '/' expr {$$ = cool::BinaryOperator::Create(BinaryKind::BO_Div, $1, $3, @1);}
    | expr '-' expr {$$ = cool::BinaryOperator::Create(BinaryKind::BO_Sub, $1, $3, @1);}
    | expr '+' expr {$$ = cool::BinaryOperator::Create(BinaryKind::BO_Add, $1, $3, @1);}
    | expr LE expr  {$$ = cool::BinaryOperator::Create(BinaryKind::BO_LE, $1, $3, @1);}
    | expr '<' expr {$$ = cool::BinaryOperator::Create(BinaryKind::BO_LT, $1, $3, @1);}
    | expr '=' expr {$$ = cool::BinaryOperator::Create(BinaryKind::BO_EQ, $1, $3, @1);}
    | NOT expr      {$$ = cool::UnaryOperator::Create(UnaryKind::UO_Not, $2, @1);}
    | OBJECTID ASSIGN expr  {$$ = cool::Assign::Create($1, $3, @1);}
    ;


let_list :
    OBJECTID ':' TYPEID optinit IN expr  {$$ = cool::Let::Create($1, $3, $4, $6, @1); }
    | OBJECTID ':' TYPEID optinit ',' let_list  {$$ = cool::Let::Create($1, $3, $4, $6, @1); }
    | error let_list  {$$ = $2; }  // Go on to the next variable if the current one is busted
    // possible bug: The final formal mustbe correct
    ;

optinit :
    /* empty */ {$$ = cool::NoExpr::Create();}
    | ASSIGN expr {$$ = $2; }
    ;

/* List of expressions for block */
expr_list :
    expr ';'               {$$ = cool::Expressions::Create($1);}
    | error ';'            {$$ = cool::Expressions::Create();} // create an empty expression
    | expr_list expr ';'   {$$ = ($1)->push_back($2);}
    | expr_list error ';'  {$$ = $1; }
    ;


/* List of expressions for function dispatches */
expr_list_2 :
    /* empty */             {$$ = cool::Expressions::Create(); }
    | expr_list_2_pr        {$$ = $1;}
    ;

expr_list_2_pr :
    expr                        {$$ = cool::Expressions::Create($1);}
    | expr_list_2_pr ',' expr   {$$ = ($1)->push_back($3);}
    ;

formal_list :
    /* empty */         {$$ = cool::Formals::Create();}
    | formal_list_pr    {$$ = $1;}
    ;

formal_list_pr :
    formal                          {$$ = cool::Formals::Create($1);}
    | formal_list_pr ',' formal     {$$ = ($1)->push_back($3);}
    ;

formal :
    OBJECTID ':' TYPEID    {$$ = cool::Formal::Create($1, $3, @1);}


kase_list :
    kase ';'               {$$ = cool::KaseBranches::Create($1);}  // Create a vector
    | kase_list kase ';'   {$$ = ($1)->push_back($2);}
    ;


kase :
    OBJECTID ':' TYPEID DARROW expr {$$ = cool::KaseBranch::Create($1, $3, $5, @1);}
    ;

/* end of grammar */
%%

/* This function is called automatically when Bison detects a parse error. */
void yyerror(const char *s) {
    extern cool::SourceLoc gCurrLineNo;

    std::cerr << "\"" << gCurrFilename << "\", " << "line " << gCurrLineNo << ": " << s << " at or near ";
    cool::print_cool_token(std::cerr, yychar);
    std::cerr << std::endl;

    if (++omerrs > 50) {
        std::cerr << "More than 50 errors" << std::endl;
        exit(1);
    }
}
