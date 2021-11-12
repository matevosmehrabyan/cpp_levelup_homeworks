#include "client.h"


Client::Client() {};

void Client::addCallback(const thread_func func) {
    callback_functions.insert(func);
}

std::set<thread_func>* Client::getCallbacks() {
    return &this->callback_functions;
}