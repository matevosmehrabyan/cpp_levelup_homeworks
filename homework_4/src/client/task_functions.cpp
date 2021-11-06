#include <iostream>

#include "task_functions.h"


void* sayHello(void* ptr) {
    std::string* name = static_cast<std::string*>(ptr);
    std::cout << "Hello " << *name << std::endl;
}

void* isEven(void* ptr) {
    int* number = static_cast<int*>(ptr);
    return *number % 2 ;
}


void* square(void* ptr) {
    int* number = static_cast<int*>(ptr);
    return (*number) * (*number);
}