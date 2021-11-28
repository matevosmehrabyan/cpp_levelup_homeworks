#include "task_manager.h"

#include <iostream>
#include <cerrno>
#include "unistd.h"


size_t READ = 0;
size_t WRITE = 1;


std::string to_string(TestStatus status) {
    switch (status) {
        case SUCCESS:
            return "SUCCESS";
        case FAILURE:
            return "FAILURE";
        case UNRESOLVED:
            return "UNRESOLVED";
        default:
            return "UNKNOWN";
    }
}

TaskManager::TaskManager() {}

void TaskManager::addTask(Task& task) {
    this->tasks.push_back(task);
}

TestStatus TaskManager::runSingleTask(Task& task) {
    int fd[2];
    int pipe_creation_status = pipe(fd);
    if (pipe_creation_status == -1) {
        std::cerr << "Failed to create pipe. Error Code: " << errno << std::endl;
        return UNRESOLVED;
    }

    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Failed to start test. Error Code: " << errno << std::endl;
        return UNRESOLVED;
    }

    TestStatus status;
    if (pid == 0) {
        close(fd[READ]);
        bool test_result = false;

        try {
            test_result = task.getTaskFunc()();
        } catch (...) {
            std::cerr << "Something went wrong while running test " << task.getName() << std::endl;
            status = UNRESOLVED;
            ssize_t wr_satus = write(fd[WRITE], &status, sizeof(status));
            if (wr_satus == -1) {
                // TODO: Very bad case. Parent will hang on waiting...
                std::cerr << "Failed to write ro pipe. Exit Code: " << errno << std::endl;
            }
        }

        if (test_result) {
            status = SUCCESS;
        } else {
            status = FAILURE;
        }

        ssize_t wr_satus = write(fd[WRITE], &status, sizeof(status));
        if (wr_satus == -1) {
            std::cerr << "Failed to write ro pipe. Exit Code: " << errno << std::endl;
        }

        close(fd[WRITE]);
        exit(0);

    } else {
        close(fd[WRITE]);
        ssize_t rd_status = read(fd[READ], &status, sizeof(status));
        if (rd_status == -1) {
            std::cerr << "Failed to get the test result. Exit Code: " << errno << std::endl;
            return UNRESOLVED;
        }

        return status;
    }

};

bool TaskManager::runTasks() {
    this->statuses = std::vector<TestStatus>();
    this->status = true;
    this->success_tests_count = 0;

    for (Task& task : this->tasks) {
        TestStatus status = this->runSingleTask(task);
        if (status == SUCCESS) {
            this->success_tests_count++;
        } else {
            this->status = false;
        }
        this->statuses.push_back(status);
    }

    return this->status;
};

void TaskManager::reportResults() {
    std::cout << "-------------- Testing Results ----------" << std::endl;

    std::cout << "-------------- Tests ";
    if (this->status) {
        std::cout << "PASSED";
    } else {
        std::cout << "FAILED";
    }
    std::cout << " -------------" << std::endl;

    std::cout << "Run " << this->success_tests_count << "/" << this->statuses.size() << " passed"
              << std::endl;
    std::cout << "=========================================" << std::endl;


    for (int i = 0; i < this->statuses.size(); i++) {
        std::cout << "Test: " << this->tasks[i].getName() << ", Status: "
                  << to_string(this->statuses[i]) << std::endl;

        if (i != this->statuses.size() - 1) {
            std::cout << "-----------------------------------------" << std::endl;
        }
    }

    std::cout << "=========================================" << std::endl;
};

std::vector<std::pair<Task&, TestStatus>> TaskManager::getResults() {
    std::vector<std::pair<Task&, TestStatus>> results;
    for (int i = 0; i < this->statuses.size(); i++) {
        results.push_back(std::pair<Task&, TestStatus>(this->tasks[i], this->statuses[i]));
    }
    return results;
}
