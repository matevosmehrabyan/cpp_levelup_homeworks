#include <stdexcept>

#include "tests.h"


bool emptyTest () {
    return true;
}

bool exceptionTest() {
    throw std::runtime_error("BOOM");
    return true;
}

bool failTest() {
    return false;
}
