#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include <set>
#include "common.h"


class Client {
private:
    std::set<Handler> callback_functions;

public:
    Client();
    void addCallback(const Handler func);
    std::set<Handler>* getCallbacks();

};

#endif