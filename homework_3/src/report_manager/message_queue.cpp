#include "message_queue.h"


void MessageQueue::addMessage(const std::string message) {
    pthread_mutex_lock(&this->message_mutex);
    this->messages.push(message);
    pthread_mutex_unlock(&this->message_mutex);
}

void MessageQueue::registerHandler(void (*handler)(std::string)) {
    pthread_mutex_lock(&this->handler_mutex);
    this->handlers.push_back(handler);
    pthread_mutex_unlock(&this->handler_mutex);
}

void MessageQueue::reportMessages() {
    pthread_mutex_lock(&this->handler_mutex);
    std::vector<void (*)(std::string)> current_handlers(this->handlers);
    pthread_mutex_unlock(&this->handler_mutex);

    while (!this->messages.empty()) {
        pthread_mutex_lock(&this->message_mutex);
        std::string current_message = this->messages.front();
        this->messages.pop();
        pthread_mutex_unlock(&this->message_mutex);

        for (const auto handler : current_handlers) {
            handler(current_message);
        }
    }
}

MessageQueue::MessageQueue() {
    pthread_mutex_init(&this->message_mutex, NULL);
    pthread_mutex_init(&this->handler_mutex, NULL);
}

MessageQueue::~MessageQueue() {
    pthread_mutex_destroy(&this->message_mutex);
    pthread_mutex_destroy(&this->handler_mutex);
}