#include "message_queue.h"


void MessageQueue::addMessage(const std::string message) {
    pthread_mutex_lock(&this->message_mutex);
    this->messages.push(message);
    pthread_mutex_unlock(&this->message_mutex);
}

void MessageQueue::registerHandler(thread_func handler) {
    pthread_mutex_lock(&this->handler_mutex);
    this->handlers.push_back(handler);
    pthread_mutex_unlock(&this->handler_mutex);
}

void MessageQueue::reportMessages() {
    pthread_mutex_lock(&this->handler_mutex);
    std::vector<thread_func> current_handlers(this->handlers);
    pthread_mutex_unlock(&this->handler_mutex);

    while (!this->messages.empty()) {
        pthread_mutex_lock(&this->message_mutex);
        std::string* current_message = new std::string(this->messages.front());
        this->messages.pop();
        // TODO: Optimize this part. Storing messages in heap is expensive.
        this->handler_messages.push_back(current_message);
        pthread_mutex_unlock(&this->message_mutex);

        for (const auto handler : current_handlers) {
            pthread_t* current_handler_thread = new pthread_t();
            this->handler_threads.push_back(current_handler_thread);
            pthread_create(current_handler_thread, NULL, handler, static_cast<void*>(current_message));
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
    for (int i = 0; i < this->handler_threads.size(); i++) {
        pthread_join(*this->handler_threads[i], NULL);
        delete this->handler_threads[i];
        this->handler_threads[i] = nullptr;
    }
    for (int i = 0; i < this->handler_messages.size(); i++) {
        delete this->handler_messages[i];
        this->handler_messages[i] = nullptr;
    }
}