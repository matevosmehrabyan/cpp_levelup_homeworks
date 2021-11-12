#include <pthread.h>
#include <iostream>
#include <unistd.h>

#include "client.h"
#include "handlers.h"
#include "message_queue.h"
#include "report_handler.h"
#include "report_manager.h"



void* firstClient(void* ptr) {
    Client client;
    client.addCallback(sayHello);
    client.addCallback(sayBye);

    ReportManager* reportManager = static_cast<ReportManager*>(ptr);
    reportManager->addClient(&client);

    sleep(1);
    std::string message_1 = "First client msg_1";
    reportManager->send(&message_1);

    sleep(15);
    std::string message_2 = "First client msg_2";
    reportManager->send(&message_2);

    sleep(30);
}

void* secondClient(void* ptr) {
    Client client;
    client.addCallback(logError);

    ReportManager* reportManager = static_cast<ReportManager*>(ptr);
    reportManager->addClient(&client);

    sleep(3);
    std::string message_1 = "Second client msg_1";
    reportManager->send(&message_1);

    sleep(35);
    std::string message_2 = "Second client msg_2";
    reportManager->send(&message_2);

    sleep(30);
}

int main () {
    ReportHandler* report_handler = new MessageQueue();
    ReportManager report_manager(report_handler);
    void* report_manager_ptr = static_cast<void*>(&report_manager);

    pthread_t first_thread;
    int first_thread_status = pthread_create(&first_thread, NULL, firstClient, report_manager_ptr);
    if (first_thread_status != 0) {
        std::cerr << "First client thread failed. Error code: " << first_thread_status << std::endl;
        return 1;
    }

    pthread_t second_thread;
    int second_thread_status = pthread_create(&second_thread, NULL, secondClient, report_manager_ptr);
    if (second_thread_status != 0) {
        std::cerr << "Second client thread failed. Error code: " << second_thread_status << std::endl;
        pthread_join(first_thread, NULL);
        return 1;
    }

    sleep(1);
    std::string message = "Main message";
    report_manager.send(&message);

    int iterations_count = 5;
    for (int i = 0; i < iterations_count; i++) {
        std::cout << "--------------------------" << std::endl;
        sleep(10);
        report_manager.report();
    }

    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);

    return 0;
}
