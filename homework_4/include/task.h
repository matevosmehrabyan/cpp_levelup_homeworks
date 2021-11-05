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
    Task(task_func func, void* arg);
    Task(Task& tast);
    ~Task();

    TaskStatus getStatus();
    void setStatus(TaskStatus s);

    task_func getRunner();
    const void* getArg();

private:
    task_func runner;
    void* arg;

    TaskStatus status;
    pthread_mutex_t status_mutex;
};

#endif