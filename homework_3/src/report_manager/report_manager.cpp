#include "report_manager.h"

ReportManager::ReportManager(ReportHandler* report_handler) {
    this->report_handler = report_handler;
    pthread_mutex_init(&this->client_mutex, NULL);
}

ReportManager::~ReportManager() {
    pthread_mutex_destroy(&this->client_mutex);
}

void ReportManager::addClient(Client* client) {
    pthread_mutex_lock(&this->client_mutex);
    this->clients.insert(client);
    pthread_mutex_unlock(&this->client_mutex);

    for (auto callback_func : *client->getCallbacks()) {
        this->report_handler->registerHandler(callback_func);
    }
}

void ReportManager::send(std::string* msg) {
    this->report_handler->addMessage(*msg);
}

void ReportManager::report() {
    this->report_handler->reportMessages();
}
