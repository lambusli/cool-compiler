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

To implement the stack, I used one main class `Stack` and subclasses: `Cons`, `Cons_plus`, and `Cons_swap`. The `Stack` class takes care of the major operations when the stack is empty. The `Cons` class takes care of the major operations when the stack is not empty. `Cons_plus` takes care of the operation of `+` command. `Cons_swap` takes care of the operation of `s` command.

Suppose variable `myStack` has type `Stack`. Then we can perform the following operations:

* `myStack <- myStack.push(s : String)` Push a new string onto the stack top.
* `myStack <- myStack.pop()` Remove the top element.
* `myStack.size()` Return the number of elements the stack contains.
* `myStack.top()` Return the top element of the stack.
* `myStack.display()` Display all elements of the stack.
* `myStack.eval()` Evaluate the stack as specified by the `e` command.


2. List 3 things that you like about the Cool programming language.

* Nothing.
* Nothing.
* Nothing.


3. List 3 things you *don't* like about Cool.

* It is not allowed to declare a pointer attribute that points to a SELF_TYPE. Something equivalent or similar must be done by defining subclasses.

* A conditional must contain `else` statements. Sometimes I have to be clever about how to execute nothing by writing some code.

* The syntax for local variable `let ... in` is awful. Such nesting structure creates unnecessary complexity.

* Lack of `return` keyword freaks me out. 
