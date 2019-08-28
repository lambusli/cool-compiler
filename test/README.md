# CS433 Testing Infrastructure

For your convenience, your compiler skeleton includes the same test infrastructure used to evaluate your submissions (but not the tests themselves). You can use this infrastructure to run multiple test scenarios and/or implement unit tests.

You can run all of these tests (for all phases of the compiler and the unit tests) from within your project with:

```
make test CTEST_OUTPUT_ON_FAILURE=TRUE
```

The latter variable is set to ensure [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) (part of CMake) displays the messages from the test runner on error.

## Integration Tests

In the `integration` sub-directory you will find test runners and additional sub-directories for each phase with the respective tests. You should not need to modify the runners. You may to wish to modify the `CMakeLists.txt` file to control whether the tests use your implementations for all phases, or just the phase being tested (the default).

To run a single integration test suite, e.g. just for the lexer, use `ctest` directly:

```
CTEST_OUTPUT_ON_FAILURE=TRUE ctest -R lexer
```

Replace `lexer` with `parser`, `semant`, or `cgen` for the other phases.

Within each phase directory, e.g. `lexer`, you can define a new test by creating a input file (typically Cool code) ending with `.test`. You then need to define the expected `stdout` and `stderr` output. The test runner will compare the output of the program-under-test to these files. Note that the runner expects the `stdout` and `stderr` files have the same name as the test file with ".stdout" and ".stderr" appended, respectively. To help you create the reference outputs there are additional `make` targets for each phase that will run all of your test inputs through the reference compiler. For example to create the reference outputs for your parser tests, you can run:

```
make parser_ref_test
```

There is a corresponding target for each phase (i.e. `lexer_ref_test`, `semant_ref_test` and `cgen_ref_test`).

## Unit Tests

Unit tests are implemented with [Google Test](https://github.com/google/googletest), refer to the existing tests and the online documentation for how to implement additional tests.

Note that before you can run the unit tests, you will need to build the unit test executable with

```
make midd-cool-test
```
