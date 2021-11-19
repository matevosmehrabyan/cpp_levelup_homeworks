#ifndef REPORT_HANDLER_H
#define REPORT_HANDLER_H

#include <string>

#include "common.h"


class ReportHandler {
public:
    virtual void addMessage(std::string)=0;
    virtual void registerHandler(Handler handler)=0;
    virtual void reportMessages()=0;
};

#endif