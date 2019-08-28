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
#include <fstream>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "ast.h"
#include "cgen.h"

// Lexer and parser associated variables
extern int yy_flex_debug;                // Control Flex debugging (set to 1 to turn on)
std::istream *gInputStream = &std::cin;  // istream being lexed/parsed
const char *gCurrFilename = "<stdin>";   // Path to current file being lexed/parsed
extern int ast_yydebug;                  // Control Bison debugging (set to 1 to turn on)
extern int ast_yyparse(void);            // Entry point to the AST parser
extern cool::Program *gASTRoot;          // AST produced by parser

namespace {

void usage(const char *program) {
  std::cerr << "Usage: " << program << " [-crgtTO] [-o file]" << std::endl;
}
}

int main(int argc, char *argv[]) {
  yy_flex_debug = 0;
  std::string out_filename;

  int c;
  opterr = 0;  // getopt shouldn't print any messages
  while ((c = getopt(argc, argv, "lpscrgtTOo:h")) != -1) {
    switch (c) {
      case 'l':
        yy_flex_debug = 1;
        spdlog::set_level(spdlog::level::debug);
        break;
      case 'p':
        ast_yydebug = 1;
        spdlog::set_level(spdlog::level::debug);
        break;
      case 'c':
        spdlog::set_level(spdlog::level::debug);
        break;
      case 'r':
        disable_reg_alloc = 1;
        break;
      case 'g':  // enable garbage collection
        cgen_Memmgr = GC_GENGC;
        break;
      case 't':  // run garbage collection very frequently (on every allocation)
        cgen_Memmgr_Test = GC_TEST;
        break;
      case 'T':  // do even more pedantic tests in garbage collection
        cgen_Memmgr_Debug = GC_DEBUG;
        break;
      case 'o':  // set the name of the output file
        out_filename = optarg;
        break;
      case 'O':  // enable optimization
        cgen_optimize = true;
        break;
      case 'h':
        usage(argv[0]);
        return 0;
      case '?':
        usage(argv[0]);
        return 85;
      default:
        break;
    }
  }

  auto firstfile_index = optind;

  ast_yyparse();

  // Don't touch the output file until we know that earlier phases of the
  // compiler have succeeded.
  if (out_filename.empty() && firstfile_index < argc) {  // no -o option
    using std::string;
    out_filename = argv[firstfile_index];
    auto i = out_filename.rfind('.', out_filename.length());

    // Replace extension with ".s" or append ".s" if no extension
    if (i != string::npos) {
      out_filename.replace(i, out_filename.size() - i, ".s");
    } else {
      out_filename += ".s";
    }
  }

  if (!out_filename.empty()) {
    std::ofstream output_stream(out_filename);
    if (!output_stream) {
      std::cerr << "Cannot open output file " << out_filename << std::endl;
      exit(1);
    }
    Cgen(gASTRoot, output_stream);
  } else {
    Cgen(gASTRoot, std::cout);
  }

  return 0;
}
