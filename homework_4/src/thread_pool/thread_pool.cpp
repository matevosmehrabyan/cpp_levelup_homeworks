#include "thread_pool.h"

void* ThreadPool::taskRunner(void* args){
    while (true) {
        pthread_mutex_lock(&this->task_mutex);
        while (this->tasks.empty()) {
            pthread_cond_wait(&this->thread_cond, &this->task_mutex);
        }

        // TODO: Get the message and process it

    }
}