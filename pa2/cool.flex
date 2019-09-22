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

%}





    /* In this section, anything not Flex must be indented */

    /*
     * Define names for regular expressions here.
     */



    /* Define additional start conditions in addition to INITIAL (all rules without an explicit start condition) */

    /* Automatically report coverage holes */
%option nodefault






%%
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
    /*
     *  The multiple-character operators.
     */

"=>" { return (DARROW); }

    /*
    * Keywords are case-insensitive except for the values true and false,
    * which must begin with a lower-case letter.
    */
class {return (CLASS);}
else {return (ELSE);}
false {
    yylval.expression = cool::BoolLiteral::Create(false, gCurrLineNo);
    return (BOOL_CONST);
}
fi {return (FI);}
if {return (IF);}
in {return (IN);}
inherits {return (INHERITS);}
isvoid {return (ISVOID);}
let {return (LET);}
loop {return (LOOP);}
pool {return (POOL);}
then {return (THEN);}
while {return (WHILE);}
case {return (CASE);}
esac {return (ESAC);}
new {return (NEW);}
of {return (OF);}
not {return (NOT);}
true {
    yylval.expression = cool::BoolLiteral::Create(true, gCurrLineNo);
    return (BOOL_CONST);
}
    /*
    *  String constants (C syntax, taken from lexdoc(1) )
    *  Escape sequence \c is accepted for all characters c. Except for
    *  \n \t \b \f, the result is c. (but note that 'c' can't be the NUL character)
    */

%%
