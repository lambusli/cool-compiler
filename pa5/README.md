# CS433 Programming Assignment 5: Code Generation

## Files

Your directory should contain the following files:

1. `CMakeLists.txt`: CMake file for building the code generator. You should not need to modify this file.
1. `cgen-main.cc`: Executable for your code generator. You should not need to modify this file.
1. `mycoolc`: A bash-script to connect your code generator to the reference components to facilitate testing.
1. `example.cl`: This file should contain a test program of your own design. Test as many features of the code generator as you can. You can also use the integration test infrastructure in `test/integration`, or add more files to your project in this assignment directory. 
1. `README.md`: This file. You will need to edit the README file with your write-up.

Like PA4 you will also need to modify files in the `src` directory. Specifically (but not limited to):

1. `src/include/ast.h`: Header for AST nodes
1. `src/include/cgen.h`: Header for classes and functions used in code generation
1. `src/cgen.cc`: Implementation files for classes and functions used in code generation

You may find the support code in `src/emit.h` and `src/include/ast_consumer.h` helpful, but you are not obligated to use that code.

## Instructions

To build the code generator
```
make cgen
```
and test it in isolation:
```
./mycoolc example.cl
```

The above will generation `example.s`. To run the corresponding assembly file with SPIM:

```
../bin/spim -- -file example.s
```

*Note* the double dashes: The double dashes are required and separate the arguments to the script that runs `cool-spim` (the actual simulator executable) and the arguments to `cool-spim` itself. 

You can compare the output of your code generator to that of the reference implementation:

```
./mycoolc -C ../bin/cgen example.cl
../bin/spim -- -file example.s
```

Your assembly is not expected to match that produced by the reference implementation, but the generated code should produce the same results. Thus to test your code generator you will need to write Cool programs that generate some kind of output during execution (e.g. print the result of a computation).

To enable optional debugging add `-c` after a `--`, e.g.
```
./mycoolc -- -c example.cl
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
