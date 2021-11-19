#include "client.h"


Client::Client() {};

void Client::addCallback(const Handler func) {
    callback_functions.insert(func);
}

std::set<Handler>* Client::getCallbacks() {
    return &this->callback_functions;
}