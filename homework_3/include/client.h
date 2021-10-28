#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include "common.h"

class Client {
private:
    pthread_t runner;
    std::vector<handler> handlers;

public:
    Client();
};


#endif