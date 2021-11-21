# Simple Thread Pool Implementation

Sources can be used in projects where it is needed.

# Dependencies

1) Make
2) CMake
3) g++

## Build

The thread pool will be built as library to use in various projects. A simple use case was added for demonstrating the usage of thread pool.
For building the demo, do the following steps:
1. `cmake .`
2. `make`

After executing the above commands, a library `libthreadpool.so` and a binary file `demo` will be built.
The `libthreadpool.so` library contains the thread pool implementation which can be used where it is needed.

The `demo` is a binary file which demonstrates the usage of thread pool library. Just run it by typing `./demo`
