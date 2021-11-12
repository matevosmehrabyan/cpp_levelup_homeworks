#include <iostream>

#include "thread_pool.h"


void* taskRunner(void* arg){
    ThreadData* thread_data = static_cast<ThreadData*>(arg);
    while (true) {
        pthread_mutex_lock(&thread_data->task_mutex);
        while (thread_data->tasks.empty()) {
            pthread_cond_wait(&thread_data->thread_cond, &thread_data->task_mutex);

            if (thread_data->must_stop) {
                pthread_mutex_unlock(&thread_data->task_mutex);
                return nullptr;
            }
        }

        Task task(thread_data->tasks.front());
        thread_data->tasks.pop();
        pthread_mutex_unlock(&thread_data->task_mutex);

        task.getRunner()(task.getArg());
    }
    return nullptr;
}

ThreadData::ThreadData() {
    this->must_stop = false;
    pthread_mutex_init(&this->task_mutex, NULL);
    pthread_cond_init(&this->thread_cond, NULL);
}

ThreadData::~ThreadData() {
    pthread_mutex_destroy(&this->task_mutex);
    pthread_cond_destroy(&this->thread_cond);
}

ThreadPool::ThreadPool(size_t threads_count) {
    this->threads_count = threads_count;
    this->thread_data = new ThreadData();
}

void ThreadPool::start() {
    for (int i = 0; i < this->threads_count; i++) {
        this->threads.push_back(pthread_t());
        int status = pthread_create(&this->threads[i], NULL, taskRunner, this->thread_data);

        if (status != 0) {
            std::cerr << "Failed to start runner thread" << std::endl;
        }
    }
}

ThreadPool::~ThreadPool() {
    pthread_mutex_lock(&this->thread_data->task_mutex);
    this->thread_data->must_stop = true;
    pthread_mutex_unlock(&this->thread_data->task_mutex);
    pthread_cond_broadcast(&this->thread_data->thread_cond);

    for (pthread_t& thread : this->threads) {
        pthread_join(thread, NULL);
    }

    pthread_mutex_destroy(&this->thread_data->task_mutex);
    pthread_cond_destroy(&this->thread_data->thread_cond);
}

void ThreadPool::addTask(Task task) {
    pthread_mutex_lock(&this->thread_data->task_mutex);
    this->thread_data->tasks.push(task);
    pthread_mutex_unlock(&this->thread_data->task_mutex);
    pthread_cond_signal(&this->thread_data->thread_cond);
}