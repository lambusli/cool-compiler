/*
 * The scanner definition for COOL.
 */

/*
 * Code enclosed in %{ %} in the first section is copied verbatim to the
 * output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything from the skeleton.
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

#include <string>
#include <istream>

#include "ast.h"
#include "cool_parse.h"
#include "stringtab.h"
#include "utilities.h"

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1024

#define YY_NO_UNPUT   /* keep g++ happy */
#define yywrap() 1
#define YY_SKIP_YYWRAP


extern std::istream* gInputStream;

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
    gInputStream->read((char*)buf, max_size); \
    if ((result = gInputStream->gcount()) < 0) { \
        YY_FATAL_ERROR("read() in flex scanner failed"); \
    }


/* String buffer for assembling string constants */
std::string string_buf;


extern cool::SourceLoc gCurrLineNo;

extern YYSTYPE cool_yylval;

/*
 * Add your own definitions here
 */
int comment_depth = 0;
%}





    /* In this section, anything not Flex must be indented */

    /*
     * Define names for regular expressions here.
     */
typeID [A-Z][a-zA-Z0-9_]*
objectID [a-z][a-zA-Z0-9_]*


    /* Define additional start conditions in addition to INITIAL (all rules without an explicit start condition) */
%x NESTEDCOMMENT
%x LINECOMMENT
%x STRING


    /* Automatically report coverage holes */
%option nodefault






%%
    /*
    * Keywords are case-insensitive except for the values true and false,
    * which must begin with a lower-case letter.
    */
(?i:class) {return (CLASS);}
(?i:else) {return (ELSE);}
f(?i:alse) {
    yylval.expression = cool::BoolLiteral::Create(false, gCurrLineNo);
    return (BOOL_CONST);
}
(?i:fi) {return (FI);}
(?i:if) {return (IF);}
(?i:in) {return (IN);}
(?i:inherits) {return (INHERITS);}
(?i:isvoid) {return (ISVOID);}
(?i:let) {return (LET);}
(?i:loop) {return (LOOP);}
(?i:pool) {return (POOL);}
(?i:then) {return (THEN);}
(?i:while) {return (WHILE);}
(?i:case) {return (CASE);}
(?i:esac) {return (ESAC);}
(?i:new) {return (NEW);}
(?i:of) {return (OF);}
(?i:not) {return (NOT);}
t(?i:rue) {
    yylval.expression = cool::BoolLiteral::Create(true, gCurrLineNo);
    return (BOOL_CONST);
}


    /* Identifiers */
{typeID} {
    yylval.symbol = cool::gIdentTable.emplace(yytext, yyleng);
    return (TYPEID);
}

{objectID} {
    yylval.symbol = cool::gIdentTable.emplace(yytext, yyleng);
    return (OBJECTID);
}


    /* New line */
"\n" {gCurrLineNo++; }


    /* White space */
[ \t\f\v\r]+ {/* Do nothing */}


    /* Integer */
[0-9]+ {
    try {
        int num = std::stoi(std::string(yytext, yytext + yyleng));
        yylval.expression = cool::IntLiteral::Create(num, gCurrLineNo);
        return (INT_CONST);
    } catch(std::out_of_range& e) {
        yylval.error_msg = "Integer literal is out of range";
        return (ERROR);
    }
}


    /*
     *  Nested comments
     */
<INITIAL>{
    "(*" {
        comment_depth ++;
        BEGIN(NESTEDCOMMENT);
    }
    "*)" {
        yylval.error_msg = "Unmatched *)";
        return (ERROR);
    }
}

<NESTEDCOMMENT>{
    "(*" {comment_depth++;}
    "*)" {
        comment_depth--;
        if (comment_depth == 0) {BEGIN(INITIAL);}
    }
    [^(*\n]+ {}
    "*" {}
    "(" {}
    "\n" {gCurrLineNo++;}
    <<EOF>> {
        BEGIN(INITIAL);
        yylval.error_msg = "EOF in comment";
        return (ERROR);
    }
}


    /* Line comments */
<INITIAL>"--" {
    BEGIN(LINECOMMENT);
}

<LINECOMMENT>{
    "\n" {gCurrLineNo++; BEGIN(INITIAL);}
    [^\n] {}
}




    /*
     *  The multiple-character operators.
     */
"=>" { return (DARROW); }



    /*
    *  String constants (C syntax, taken from lexdoc(1) )
    *  Escape sequence \c is accepted for all characters c. Except for
    *  \n \t \b \f, the result is c. (but note that 'c' can't be the NUL character)
    */
<INITIAL>"\"" {
    string_buf.clear();
    BEGIN(STRING);
}

<STRING>{

    /* Escape */
    "\\\"" { string_buf += '\"'; }
    \\[^ntbf] { string_buf += yytext[1]; }
    "\\n" { string_buf += '\n'; }
    "\\t" { string_buf += '\t'; }
    "\\b" { string_buf += '\b'; }
    "\\f" { string_buf += '\f'; }

    /* End of string */
    "\"" {
        yylval.expression = cool::StringLiteral::Create(string_buf, gCurrLineNo);
        /* Test what the final string actually is
        * const char *temp = string_buf.c_str();
        * printf("temp = %s\n", temp);
        */
        string_buf.clear();
        BEGIN(INITIAL);
        return (STR_CONST);
    }

    /* New line */
    "\n" {
        yylval.error_msg = "Unterminated string constant";
        gCurrLineNo++;
        BEGIN(INITIAL);
        return (ERROR);
    }

    /* End of file */
    <<EOF>> {
        /* Cannot be tested because Atom saves with an automatic newline */
        yylval.error_msg = "EOF in string constant";
        BEGIN(INITIAL);
        return (ERROR);
    }

    /* Null char error */
    "\0" {
        yylval.error_msg = "String contains null character";
        BEGIN(INITIAL);
        return (ERROR);
    }

    /* Anything else */
    [^"\n\\]* {
        string_buf += yytext;
    }
}

    /* Whatever */
[\(\[\{\)\]\}:.;,<=+->] {/* Do nothing temporarily */}
"<-" {/* Do nothing temporarily */}




<<EOF>> {yyterminate();}
%%
