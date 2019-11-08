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
The majority of implementation is in ../src/semant.cc

Line 146 ~ 177 is the main function that executes all the subroutines of typechecking: 1. Constructing inheritance graph of classes; 2. Creating Scoped Tables of objects and methods; 3. The actual typechecking. Notice that I abort the execution of program if any one subroutine detects error. This is to avoid cascading error that makes absolutely no sense. Within each subroutine, errors are recoverable.

Line 97 ~ 143 is the constructor of SemantKlassTable. Within this constructor, an inheritance graph of classes is created. We check for errors such as repeating definition and cyclic inheritance graph. Notice that cyclic inheritance graph can be spotted by checking whether the inheritance is connected. If the graph is separated into forest, then there are cycles.

Line 221 ~ 327 is the function that creates all scoped tables. We use ScopedTable to store the scopes of each class. If class B inherits class A, then we first copy the scoped tables of A into B so that B inherits every method and attribute from A, and then use AddToScope() function to add attributes and methods newly defined in B.
We detect errors such as repeating attribute, inconsistent method definition between ancestors and childrens.

Line 331 ~ 439 are helper functions related to Semantic Environment. The functions include the following functionalities: 1. recursively traverse all the SemantNode to do typechecking; 2. Create and adjust new semantic environment when we are under a different class; 3. implementation of <= and LUB.

Line 447 ~ 886 are all the typechecking functions for AST nodes. The typechecking process happens recursively: the type of a parent AST node depends on the types of its children.

My testing approach is generally "write a little bit codes and then test." At each mini-step: inheritance graph, checking for repetitions, scoped tables, typechecking for each ASTnode, I stopped and came up with both good and bad examples. 

Final remark on the resolution of SELF_TYPE. I mention this issue because the sheer number of bugs related to this issue calls my attention. Generally, SELF_TYPE is not resolved if we just perform <= or LUB operation. However, in [Dispatch] and [StaticDispatch], SELF_TYPE is resolved under two circumstances: 1. when an argument of dispatch evaluates to SELF_TYPE; 2. when the declared type of the method is SELF_TYPE.
SELF_TYPE is resolved under scenario 1, because we need to compare whether an argument's type is consistent with the definition of formal. Since formal cannot have SELF_TYPE and the comparison has to happen, we resolve the SELF_TYPE of the argument in dispatch.
SELF_TYPE is resolved under scenario 2. Consider this example:
```
true = true.copy()
```
This expression should evaluates to Bool. However, since .copy() function evalutes to SELF_TYPE, if SELF_TYPE does not resolve here, then the [Compare] rule is no longer valid and the expression evaluates to Object.
