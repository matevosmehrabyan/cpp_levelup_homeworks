#ifndef COMMON_H
#define COMMON_H

#include <string>


typedef void (*handler)(std::string);
typedef void (*thread_func)(void*);

#endif