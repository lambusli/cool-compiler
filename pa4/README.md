# CS433 Programming Assignment 4: Semantic Analysis

## Files

Your directory should contain the following files:

1. `CMakeLists.txt`: CMake file for building the semantic analyzer. You should not need to modify this file.
1. `semant-main.cc`: Executable for your semantic analyzer. You should not need to modify this file.
1. `mysemant`: A shell-script to connect your semantic analyzer to the reference lexer and parser to facilitate testing.
1. `good.cl`, `bad.cl`: Files to test a few features of the semantic analyzer. You should add tests to ensure that good.cl exercises as many legal semantic combinations as possible and that bad.cl exercises as many different semantics errors as you can incorporate into one file. If you can't integrate all of your tests into these files, or want to break your test suite into multiple files, you can also use the integration test infrastructure in the `test/integration` directory, or add more files to your project in this assignment directory.
1. `README.md`: This file. You will need to edit the README file with your write-up.

Unlike past assignments, you will also need to modify files in the `src` directory. Specifically (but not limited to):

1. `src/include/ast.h`: Header for AST nodes
1. `src/include/semant.h`: Header for classes and functions used in semantic analysis
1. `src/semant.cc`: Implementation files for classes and functions used in semantic analysis

You may find the support classes in `src/include/ast_consumer.h` helpful, but you are not obligated to use that code.

## Instructions

To build the semantic analyzer
```
make semant
```
and test it in isolation:
```
./mysemant good.cl
```

You can compare the output of your parser to that of the reference
implementation
```
./mysemant -S ../bin/semant good.cl
```
or use your lexer as part of the entire Cool compiler.
```
../bin/mycoolc -S ./semant good.cl
```

To enable optional debugging add `-s` after a `--`, e.g.
```
./mysemant -- -s good.cl
```

This flag sets the [spdlog](https://github.com/gabime/spdlog) log to level to "debug", such that all "debug" or more serious messages are printed to stderr. You will need to add your own debug messages, e.g.:
```cpp
spdlog::debug("Something unexpected happened in my program");
```

If you get compiler errors that `spdlog` is not found, you will need to import the library with:
```cpp
#include "spdlog/spdlog.h"
```

Instructions for turning in the assignment will be posted on the course site. Make sure to complete the writeup below.

## Write-up

Replace with a brief write-up of your implementation as described in the assignment PDF.
