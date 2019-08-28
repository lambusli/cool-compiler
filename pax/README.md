# CS433 Programming Assignment X: Optimization

## Files

Your directory should contain the following files:

1. `CMakeLists.txt`: CMake file for building the code generator. You should not need to modify this file.
1. `mycoolc`: A bash-script to connect your code generator to the reference components to facilitate testing.
1. `README.md`: This file. You will need to edit the README file with your write-up.

Unlike past assignments there is no new executable for this assignment, you will be building the `cgen` executable from PA5. As a convenience, a compile target is created in this directory to build `cgen`. However you will be modifying the same files as PA5 and the resulting `cgen` executable should be identical.

## Instructions

To build the code generator:
```
make opt
```
and test from within the project directory it with your optimizations "turned on":
```
./mycoolc -- -O -o hello_world.s ../examples/hello_world.cl
```

The above will generate `hello_world.s` (as specified with the `-o` option). To run the corresponding assembly file with SPIM and report execution statistics:

```
../bin/spim -- -keepstats -file hello_world.s
```

the result of which is

```
Loaded: ../bin/trap.handler
Hello, World.
COOL program successfully executed
Stats -- #instructions : 154
         #reads : 27  #writes 22  #branches 34  #other 71
```

*Note* the double dashes for both `spim` and `mycoolc`: these are required and separate the arguments to those scripts from the arguments to the underlying executables. In short arguments before the dashes are used to change which executables are used, the arguments after the dashes modify the behavior of the compiler itself.

You can compare the output of your code generator to that of the reference implementation:

```
./mycoolc -C ../bin/cgen -- -o hello_world.s ../examples/hello_world.cl
../bin/spim -- -keepstats -file hello_world.s
```

Note that the optimization flag just sets the global variable `cgen_optimize` to be true, you will need implement the optimization code that is activated by that variable, e.g.
```cpp
if (cgen_optimize) {
  // My awesome optimization...
}
```

Instructions for turning in the assignment will be posted on the course site. Make sure to complete the writeup below.

## Write-up

Replace with a brief write-up of your implementation as described in the assignment PDF.
