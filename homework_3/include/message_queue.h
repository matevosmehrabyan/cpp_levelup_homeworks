#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <string>
#include <queue>
#include <pthread.h>

#include "common.h"


class MessageQueue {
public:

    void AddMessage(std::string);
    void RegisterHandler(void (*handler)(std::string));

private:
    std::queue<void (*)(std::string)> handlers;
    std::queue<std::string> messages;

    pthread_mutex_t handler_mutex;
    pthread_mutex_t message_mutex;
};

#endif