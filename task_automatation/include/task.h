#ifndef TASK_H
#define TASK_H

#include <string>


typedef bool (*TaskFunc)();


class Task {
public:
    Task(TaskFunc task, std::string name);
    TaskFunc getTaskFunc();
    std::string getName();

private:
    TaskFunc task_func;
    std::string name;
};

#endif