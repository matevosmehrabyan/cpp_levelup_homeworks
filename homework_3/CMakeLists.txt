cmake_minimum_required(VERSION 3.10)

project(MessageQueue)

add_executable(message_queue ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/message_queue/message_queue.cpp)

target_include_directories(message_queue PUBLIC
                           "${PROJECT_SOURCE_DIR}/include")