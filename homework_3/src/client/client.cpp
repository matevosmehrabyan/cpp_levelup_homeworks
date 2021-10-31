#include "client.h"


Client::Client() {};

void Client::addCallback(const handler func) {
    callback_functions.insert(func);
}

std::set<handler>* Client::getCallbacks() {
    return &this->callback_functions;
}