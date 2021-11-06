cmake_minimum_required(VERSION 3.10)

project(ThreadPool)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(thread_pool ${PROJECT_SOURCE_DIR}/src/main.cpp
                           ${PROJECT_SOURCE_DIR}/src/client/client.cpp
                           ${PROJECT_SOURCE_DIR}/../common/src/handlers.cpp
                           ${PROJECT_SOURCE_DIR}/src/thread_pool/thread_pool.cpp
                           ${PROJECT_SOURCE_DIR}/src/task/task.cpp)

target_include_directories(thread_pool PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_SOURCE_DIR}/../common/include")
