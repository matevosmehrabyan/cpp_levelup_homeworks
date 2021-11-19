#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <pthread.h>
#include <string>
#include <vector>
#include <queue>

#include "report_handler.h"
#include "common.h"


class MessageQueue: public ReportHandler {
public:
    void addMessage(const std::string);
    void registerHandler(Handler handler);
    void reportMessages();
    MessageQueue();
    ~MessageQueue();

private:
    std::vector<Handler> handlers;
    std::queue<std::string> messages;
    std::vector<pthread_t*> handler_threads;
    std::vector<std::string*> handler_messages;

    pthread_mutex_t handler_mutex;
    pthread_mutex_t message_mutex;
};

#endif