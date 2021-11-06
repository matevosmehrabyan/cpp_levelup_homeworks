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
