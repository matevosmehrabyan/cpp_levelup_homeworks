#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <pthread.h>
#include <string>
#include <vector>
#include <stack>

#include "report_handler.h"
#include "thread_pool.h"
#include "common.h"


#define THREADS_COUNT 2


class MessageQueue: public ReportHandler {
public:
    void addMessage(const std::string);
    void registerHandler(Handler handler);
    MessageQueue();
    ~MessageQueue();

private:
    ThreadPool pool;
    std::vector<Handler> handlers;
    std::stack<std::string> messages;
    std::vector<std::string*> handler_messages;

    pthread_mutex_t handler_mutex;
    pthread_mutex_t message_mutex;
};

#endif