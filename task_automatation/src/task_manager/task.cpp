#include "task.h"


Task::Task(TaskFunc task, std::string name): task_func(task), name(name) {}

TaskFunc Task::getTaskFunc() {
    return this->task_func;
}

std::string Task::getName() {
    return this->name;
}
