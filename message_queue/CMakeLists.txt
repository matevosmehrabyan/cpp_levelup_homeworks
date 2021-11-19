cmake_minimum_required(VERSION 3.10)

project(MessageQueue)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(message_queue ${PROJECT_SOURCE_DIR}/src/main.cpp
                             ${PROJECT_SOURCE_DIR}/src/report_manager/report_manager.cpp
                             ${PROJECT_SOURCE_DIR}/src/report_manager/message_queue.cpp
                             ${PROJECT_SOURCE_DIR}/src/client/client.cpp
                             ${PROJECT_SOURCE_DIR}/../common/src/handlers.cpp)

target_include_directories(message_queue PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_SOURCE_DIR}/../common/include")
