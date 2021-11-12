cmake_minimum_required(VERSION 3.10)

project(ThreadPool)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(thread_pool ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(lib_thread_pool ${PROJECT_SOURCE_DIR}/src/thread_pool/thread_pool.cpp
                            ${PROJECT_SOURCE_DIR}/src/task/task.cpp
                            ${PROJECT_SOURCE_DIR}/../common/src/handlers.cpp)

target_link_libraries(thread_pool PUBLIC lib_thread_pool)

target_include_directories(lib_thread_pool PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_SOURCE_DIR}/../common/include")
