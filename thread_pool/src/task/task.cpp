#include "task.h"


Task::Task(Handler func, void *arg) {
    pthread_mutex_init(&this->status_mutex, NULL);
    this->status = INITIAL;
    this->runner = func;
    this->arg = arg;
}

Task::Task(const Task& task) {
    pthread_mutex_init(&this->status_mutex, NULL);
    this->status = INITIAL;
    this->runner = task.runner;
    this->arg = task.arg;
}

Task::~Task() {
    pthread_mutex_destroy(&this->status_mutex);
}

TaskStatus Task::getStatus() {
    pthread_mutex_lock(&this->status_mutex);
    TaskStatus current_status = this->status;
    pthread_mutex_unlock(&this->status_mutex);
    return current_status;
}

void Task::setStatus(TaskStatus s) {
    pthread_mutex_lock(&this->status_mutex);
    this->status = s;
    pthread_mutex_unlock(&this->status_mutex);
}

Handler Task::getRunner() {
    return this->runner;
}

void* Task::getArg() {
    return this->arg;
}
