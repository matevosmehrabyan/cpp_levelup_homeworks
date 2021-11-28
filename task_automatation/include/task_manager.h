#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <utility>

#include "task.h"


enum TestStatus {
    SUCCESS,
    FAILURE,
    UNRESOLVED
};


std::string to_string(TestStatus status);


class TaskManager {
public:
    TaskManager();
    void addTask(Task& task);
    bool runTasks();
    void reportResults();
    std::vector<std::pair<Task&, TestStatus>> getResults();

private:
    std::vector<Task> tasks;
    std::vector<TestStatus> statuses;
    bool status = true;
    size_t success_tests_count = 0;

    TestStatus runSingleTask(Task& task);
};

#endif