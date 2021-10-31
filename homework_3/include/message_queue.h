#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <string>
#include <queue>
#include <pthread.h>

#include "report_handler.h"
#include "common.h"


class MessageQueue: public ReportHandler {
public:
    void addMessage(const std::string);
    void registerHandler(void (*handler)(std::string));
    void reportMessages();
    MessageQueue();
    ~MessageQueue();

private:
    std::vector<void (*)(std::string)> handlers;
    std::queue<std::string> messages;

    pthread_mutex_t handler_mutex;
    pthread_mutex_t message_mutex;
};

#endif