#include <iostream>
#include <string>

#include "task.h"
#include "task_manager.h"
#include "tests.h"


int main () {
    Task t(emptyTest, std::string("EmptyTest"));
    TaskManager manager;

    manager.addTask(t);
    manager.runTasks();
    manager.reportResults();

    std::cout << std::endl << std::endl << std::endl;

    TaskManager second_manager;
    second_manager.addTask(t);

    Task t2(exceptionTest, std::string("ExceptionTest"));
    second_manager.addTask(t2);

    Task t3(failTest, std::string("FailTest"));
    second_manager.addTask(t3);
    second_manager.runTasks();
    second_manager.reportResults();


    return 0;
}