# Problem Definition
Write a C++ program, where std::cout ostream's output will be redirected to file.

# Solution
As we know, when we open a file with the `open` function, it returns its file descriptor, whose value will be the first free file descriptor. As we know, the file descriptor of `STDOUT` is `1`. At first, we will call the `close` function with `1` as argument, which will close the default `STDOUT`'s file. After it, we will call the `open` function. In this situation, the first free file descriptor will be `1`. After that, all output to `STDOUT` will be written to our file.
