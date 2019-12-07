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
Since code generation is a big project, it is impossible to address every single aspect of my design choices. I will do my best to touch on the essential ones.

1. Structure of activation records
=========================
|                       |
|  Method arguments     |
|                       |
=========================
|                       |
|  Let & case temporals |
|                       |
=========================
| Previous framepointer |   <-- fp + 8
=========================
| Previous self pointer |   <-- fp + 4
=========================
| return address        |   <-- fp + 0
=========================

When we dispatch a method, the caller is responsible for pushing all the method arguments. The callee prologue is responsible for pushing let & case temporals and callee saves. The callee epilogue is responsible for popping all the activation records (as shown in figure above), restoring the previous framepointer and self pointer, and jumping to the return address to resume the instructions.

How do we make sure that we set aside enough but minimum space for let & case temporals? Before the code generation for a method body, we pre-traverse the AST of that method body and recursively count what is the maximum number of 4-byte words we need at any given point. See the method `CountTemporal(int &num_temp, int &max_temp)` defined in multiple AST classes.

1. Tag of cool-classes and order of cool-classes
We depth-first traverse the inheritance graph of cool-classes to and assign each cool-class a tag so that:
-- all children's tag are greater than the parent's tag.
-- all children's tag are less than the parent's next sibling's tag.
These two properties allow us to efficiently compare the hierarchy of two classes in [Case].

In ClassNameTable and ClassObjectTable, all entries are sorted by the tags of classes. In this way we can treat the tag as an offset to access certain data of cool-classes.
However, Prototype objects, Dispatch tables, and `X_init` methods are not sorted by tag. Their orders are arbitrary.

1. Environment and Store
