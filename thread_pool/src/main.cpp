#include <pthread.h>
#include <iostream>
#include <unistd.h>

#include "thread_pool.h"
#include "handlers.h"
#include "task.h"


void* first_client_func(void* ptr) {
    ThreadPool* pool = static_cast<ThreadPool*>(ptr);
    std::string name = "Jim";
    Task first_task(sayHello, static_cast<void*>(&name));
    pool->addTask(first_task);

    std::string err_msg = "hacking failed";
    Task second_task(logError, static_cast<void*>(&err_msg));
    pool->addTask(second_task);

    int number = 15;
    Task third_task(printSquare, static_cast<void*>(&number));
    pool->addTask(third_task);

    sleep(10);
    return nullptr;
}

void* second_client_func(void* ptr) {
    ThreadPool* pool = static_cast<ThreadPool*>(ptr);
    std::string name = "Zeus";
    Task first_task(sayBye, static_cast<void*>(&name));
    pool->addTask(first_task);

    size_t index_of_fib_num = 6;
    Task second_task(calcFibonacci, static_cast<void*>(&index_of_fib_num));
    pool->addTask(second_task);

    sleep(20);
    return nullptr;
}

int main() {
    size_t thread_count = 2;
    ThreadPool pool(thread_count);
    pool.start();

    pthread_t first_client;
    int status = pthread_create(&first_client, NULL, first_client_func, static_cast<void*>(&pool));
    if (status != 0) {
        std::cerr << "First client failed to start" << std::endl; 
    }

    pthread_t second_client;
    status = pthread_create(&second_client, NULL, second_client_func, static_cast<void*>(&pool));
    if (status != 0) {
        std::cerr << "Second client failed to start" << std::endl; 
    }

    pthread_join(first_client, NULL);
    pthread_join(second_client, NULL);

    std::cout << "Main" << std::endl;

    return 0;
}
