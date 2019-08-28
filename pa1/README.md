# CS433 Programming Assignment 1: Introduction to Cool

## Files

Your assignment directory should contain the following files:

1. `atoi.cl`: An implementation in Cool of the string-integer conversion functions.
2. `stack.cl`: The skeleton file for your program.
3. `stack.test`: A short test input to the stack machine.
4. `README.md`: This file. You will need to edit the README file with your write-up.

## Instructions

To compile your Cool program (assuming you are in the assignment directory):

```
../bin/coolc -o stack.s stack.cl atoi.cl
```

And to run the corresponding assembly file with SPIM:

```
../bin/spim -- -file stack.s < stack.test
```

*Note* the double dashes, these are required and separate the arguments to the script that
runs `cool-spim` and the arguments to `cool-spim` itself. The `bin` directory of the skeleton will not be in your PATH by default. If you are in the `pa1` assignment directory you can use the relative paths `../bin/coolc` and `../bin/spim` to those executables as shown above. Alternately you can add the `bin` directory to your path to invoke those programs without the relative paths.
 
Instructions for turning in the assignment will be posted on the course site. Make sure to complete the writeup below.

## Write-up

1. Describe your implementation of the stack machine in a single short paragraph.


2. List 3 things that you like about the Cool programming language.


3. List 3 things you *don't* like about Cool.

