#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include <set>
#include "common.h"


class Client {
private:
    std::set<thread_func> callback_functions;

public:
    Client();
    void addCallback(const thread_func func);
    std::set<thread_func>* getCallbacks();

};

#endif