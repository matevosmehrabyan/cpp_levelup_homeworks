#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <pthread.h>

#include "common.h"

class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();
    void addTask();

private:
    size_t threads_count;
    std::queue<task_func> tasks;
    std::vector<pthread_t> threads;

    pthread_mutex_t task_mutex;
    pthread_cond_t thread_cond;

    void* taskRunner(void* args);
};


#endif