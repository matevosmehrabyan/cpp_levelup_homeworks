#ifndef TASK_H
#define TASK_H

#include <pthread.h>

#include "common.h"


enum TaskStatus {
    INITIAL,
    IN_PROGRESS,
    FINISHED
};

class Task {
public:
    Task(Handler func, void* arg);
    Task(const Task& tast);
    ~Task();

    TaskStatus getStatus();
    void setStatus(TaskStatus s);

    Handler getRunner();
    void* getArg();

private:
    Handler runner;
    void* arg;

    TaskStatus status;
    pthread_mutex_t status_mutex;
};

#endif