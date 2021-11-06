#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <queue>

#include "common.h"
#include "task.h"


void* taskRunner(void* args);


class ThreadData {
public:
    std::queue<Task> tasks;

    pthread_mutex_t task_mutex;
    pthread_cond_t thread_cond;
    bool must_stop;

    ThreadData();
    ~ThreadData();
};


class ThreadPool {
public:
    ThreadPool(size_t threads_count);
    ~ThreadPool();
    void addTask(Task task);
    void start();

private:
    size_t threads_count;
    std::vector<pthread_t> threads;
    ThreadData* thread_data;
};


#endif