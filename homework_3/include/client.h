#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include <set>
#include "common.h"


class Client {
private:
    std::set<handler> callback_functions;

public:
    Client();
    void addCallback(const handler func);
    std::set<handler>* getCallbacks();

};

#endif