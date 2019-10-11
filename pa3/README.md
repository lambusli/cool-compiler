
# CS433 Programming Assignment 3: Parsing

## Files

Your directory should contain the following files:

1. `CMakeLists.txt`: CMake file for building the parser. You should not need to modify this file.
1. `parser-main.cc`: Executable for your parser. You should not need to modify this file.
1. `myparser`: A shell-script to connect your parser to the reference lexer to facilitate testing.
1. `cool.y`: A skeleton file for the Bison specification. It already contains productions for the program and the classes. Use them as an example to write the remaining productions.
1. `good.cl`, `bad.cl` test a few features of the grammar. You should add tests to ensure that good.cl exercises every legal construction of the grammar and that bad.cl exercises as many different parsing errors as you can squeeze into one file. If you can't integrate all of your tests into these files, or want to break your test suite into multiple files, you can also use the integration test infrastructure in the `test/integration` directory.                   	
1. `README.md`: This file. You will need to edit the README file with your write-up.                                                          	

## Instructions

To build the parser
```
make parser
```
and test it in isolation:
```
./myparser good.cl
```

You can compare the output of your parser to that of the reference implementation
```
./myparser -P ../bin/parser good.cl
```
or use your lexer as part of the entire Cool compiler.
```
../bin/mycoolc -P ./parser test.cl
```

To enable the detailed Bison debugging information add `-p` after a `--`, e.g.
```
./myparser -- -p good.cl
```
This flag will also set the [spdlog](https://github.com/gabime/spdlog) log to level to "debug", such that all "debug" or more serious messages are printed to stderr. You will need to add your own debug messages, e.g.:
```cpp
spdlog::debug("Something unexpected happened in my program");
```

If you get compiler errors that `spdlog` is not found, you will need to import the library with:
```cpp
#include "spdlog/spdlog.h"
```

Instructions for turning in the assignment will be posted on the course site. Make sure to complete the writeup below.


## Write-up
The general idea behind this parser is to define all rules of productions and to define semantic actions using AST nodes. The uses of lists (for example, expr_list, let_list) allows expressing []* and []+ structure.

For error recovery, I generally used `error ';'` or `XXX_list error ';'` structure to ensure that any error in such forms of productions are recognized and skipped. Error recovery has been applied on `let`, `class`, and `feature`.

Currently identified and identified bugs:
1. The precedence rule for `let` is not clear.
1. Error recovery for `let` does not work for the last variable. For example `let v1 : nt, v2 : Int in expr` will recover, but `let v1 : nt, v2 : nt in expr` will not recover.
1. Error caused by `class Name {;` can be recovered from neither my parser nor the reference parser. 

Testing strategies:
1. Whenever I write a production, I test the validity of it immediately using correct example.
1. For error recovery example, I design edge cases for expression lists, feature lists, and let lists, and make sure the parser can recover from those errors.
