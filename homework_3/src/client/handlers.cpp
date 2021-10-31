#include <iostream>
#include "handlers.h"


void sayHello(std::string name) {
    std::cout << "Hello " << name << std::endl;
}

void sayBye(std::string name) {
    std::cout << "Bye " << name << std::endl;
}

void logError(std::string error_message) {
    std::cout << "Error: " << error_message << std::endl;
}
