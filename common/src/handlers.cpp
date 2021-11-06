#include <iostream>
#include "handlers.h"


void* sayHello(void* ptr) {
    std::string* name = static_cast<std::string*>(ptr);
    std::cout << "Hello " << *name << std::endl;
    return nullptr;
}

void* sayBye(void* ptr) {
    std::string* name = static_cast<std::string*>(ptr);
    std::cout << "Bye " << *name << std::endl;
    return nullptr;
}

void* logError(void* ptr) {
    std::string* error_message = static_cast<std::string*>(ptr);
    std::cout << "Error: " << *error_message << std::endl;
    return nullptr;
}

void* printSquare(void* ptr) {
    int* number = static_cast<int*>(ptr);
    std::cout << "Square of " << *number << " is " << (*number) * (*number) << std::endl;
    return nullptr;
}

void* calcFibonacci(void* ptr) {
    size_t* fib_number = static_cast<size_t*>(ptr);

    int fib1 = 0, fib2 = 1, tmp = 0;
    for (int i = 0; i < *fib_number; i++) {
        tmp = fib1 + fib2;
        fib1 = fib2;
        fib2 = tmp;
    }

    std::cout << "The fibonacci at index " << *fib_number << " is " << fib1 << std::endl;
    return nullptr;
}