# CS433 cool-student Skeleton

This directory contains the skeleton for the CS433 class project, the Cool compiler.  The project is broken up into 5 assignments (and an extra credit assignment), that will be completed over the semester.

This distribution contains a folder for each assignment and a set of source files shared between the assignments. Each assignment is independent and does not depend on any previous assignments. If you would like, you can start each assignment from a fresh clone of the skeleton. 

## Getting Started

To build and test your compiler you will need a modern C++ compiler (that supports c++14), cmake, flex, bison and bash. All of these are available on modern Linux or OSX systems. On other platforms, or if you don't have those prerequisites installed, the skeleton includes an Ubuntu 18.04-based Dockerfile for creating a suitable Linux container for building and testing your compiler (while editing files via your native operating system).

### Using Docker (optional)

In the root directory of the project create the Docker container with the following command (or its equivalent for your platform):

```
docker build -t midd-cool .
```

The above is a one-time operation. Whenever you are ready to begin development, in the root directory of the project launch the container as an interactive session:

```
docker run \
    --entrypoint /bin/bash \
    --rm \
    -v `pwd`:/opt/midd-cool \
    -it \
    midd-cool
```

This will launch a bash session in the container, making the current directory available inside the container. Thus any edits you make to the source code outside the container (i.e. in your editor of choice running on your native operating system) will also be immediately reflected in the container.

## Building

Once you have the dependencies installed, you will need to create the build files with CMake. For simplicity we will use an "in-source" build. From within the top-level directory:

```
cmake .
```

You should only need to do this once per clone of the skeleton (or if you pull updates the to the skeleton). You should not need to modify any of the build files themselves.

Once you have run the above command to create the build files, you can build the individual phases as described in README files in the assignment directories. You can also run the built-in test infrastructure as described below.

## Testing

The skeleton includes elements of the same test infrastructure used to evaluate your submission. You can run all of these tests (for all phases of the compiler) from the top-level directory with

```
make test CTEST_OUTPUT_ON_FAILURE=TRUE
```

Refer to the documentation in the `test` directory for more information, including how to run individual tests suites.