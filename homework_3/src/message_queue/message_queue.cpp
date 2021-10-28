#include "message_queue.h"

void MessageQueue::AddMessage(const std::string message) {
    pthread_mutex_lock(&this->message_mutex);
    this->messages.push(message);
    pthread_mutex_unlock(&this->message_mutex);
}

void MessageQueue::RegisterHandler(void (*handler)(std::string)) {
    pthread_mutex_lock(&this->handler_mutex);
    this->handlers.push(handler);
    pthread_mutex_unlock(&this->handler_mutex);
}

