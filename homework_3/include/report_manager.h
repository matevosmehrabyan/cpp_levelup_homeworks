#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include <pthread.h>
#include <vector>
#include <string>

#include "report_handler.h"
#include "client.h"


class ReportManager {
private:
    pthread_mutex_t client_mutex;
    ReportHandler* report_handler;
    std::set<Client*> clients;

public:
    ReportManager(ReportHandler* report_handler);
    ~ReportManager();
    void addClient(Client* client);
    void send(std::string* msg);
    void report();
};

#endif