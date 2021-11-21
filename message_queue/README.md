# Simple Message Queue Implementation
Form more information about what is a message queue, google it, please.

Sources can be used in projects where it is needed.

# Dependencies

1) Make
2) CMake
3) g++
4) libthreadpool

To install the libthreadpool library, you must go the the thread pool directory(`../thread_pool`) and install it.

# Build
A simple use case was added for demonstrating the usage of message queue.
For build the Demo, execute the following commands:

1) `cmake .`
2) `make`

# Run
After build, a message_queue executable must be created. Just execute it without any arguments:
`./message_queue`
