cmake_minimum_required(VERSION 3.10)

project(ThreadPool)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(demo ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(threadpool SHARED ${PROJECT_SOURCE_DIR}/src/thread_pool/thread_pool.cpp
                               ${PROJECT_SOURCE_DIR}/src/task/task.cpp
                               ${PROJECT_SOURCE_DIR}/../common/src/handlers.cpp)

target_link_libraries(demo PUBLIC threadpool)

target_include_directories(threadpool PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_SOURCE_DIR}/../common/include")
