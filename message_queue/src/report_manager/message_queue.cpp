#include "message_queue.h"


void MessageQueue::addMessage(const std::string message) {
    pthread_mutex_lock(&this->message_mutex);
    this->messages.push(message);
    void* msg_ptr = static_cast<void*>(&this->messages.top());
    pthread_mutex_unlock(&this->message_mutex);

    pthread_mutex_lock(&this->handler_mutex);
    for (auto& handler : this->handlers) {
        Task task(handler, msg_ptr);
        this->pool.addTask(task);
    }
    pthread_mutex_unlock(&this->handler_mutex);
}

void MessageQueue::registerHandler(Handler handler) {
    pthread_mutex_lock(&this->handler_mutex);
    this->handlers.push_back(handler);
    pthread_mutex_unlock(&this->handler_mutex);
}

MessageQueue::MessageQueue() : pool(THREADS_COUNT), ReportHandler() {
    pthread_mutex_init(&this->message_mutex, NULL);
    pthread_mutex_init(&this->handler_mutex, NULL);
    pool.start();
}

MessageQueue::~MessageQueue() {
    pthread_mutex_destroy(&this->message_mutex);
    pthread_mutex_destroy(&this->handler_mutex);
    for (int i = 0; i < this->handler_messages.size(); i++) {
        delete this->handler_messages[i];
        this->handler_messages[i] = nullptr;
    }
}