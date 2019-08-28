# CS433 Programming Assignment 2: Lexing

## Files

Your directory should contain the following files:

1. `CMakeLists.txt`: CMake file for building the lexer. You should not need to modify this file.
1. `lexer-main.cc`: Executable for your lexer. You should not need to modify this file.
1. `cool.flex`: A skeleton file for the Flex specification. You should complete this file with your regular expressions, patterns and actions (and any relevant support code you need).
1. `test.cl`: A COOL program that you can use to test the lexical analyzer.

    The file contains some errors, so it won't compile with `coolc`, but we don't need the input to be a valid COOL program to test the lexer (and in fact it is easier to write test inputs if you don't worry about writing a valid program).
    
    `test.cl` does not exercise all lexical constructs of COOL. Part of your assignment is to rewrite `test.cl` with a more complete set of tests for your lexical analyzer. If you can't integrate all of your tests into a single file, or want to break your test suite into multiple files, you can also use the integration test infrastructure in the `test/integration` directory.

1. `README.md`: This file. You will need to edit the README file with your write-up. 

As part of the assignment you likely need to consult the files in the `src` directory, but should not need to modify them (for this assignment).

## Instructions

To build the lexer
```
make lexer
```
and test it in isolation:
```
./lexer test.cl > test.tokens
```

You can compare the output of your lexer to that of the reference lexer
```
../bin/lexer test.cl
```
or use your lexer as part of the entire Cool compiler.
```
../bin/mycoolc -L ./lexer test.cl
```

To enable the detailed Flex debugging information showing which rule matched for each token, add a `-l` option, e.g.
```
./lexer -l test.cl
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

Replace with a brief write-up of your implementation as described in the assignment PDF.
