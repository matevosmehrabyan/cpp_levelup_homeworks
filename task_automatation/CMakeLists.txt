cmake_minimum_required(VERSION 3.10)

project(TaskAutomatation)

add_executable(demo ${PROJECT_SOURCE_DIR}/src/main.cpp
	            ${PROJECT_SOURCE_DIR}/src/tests/tests.cpp)

add_library(taskmanager SHARED ${PROJECT_SOURCE_DIR}/src/task_manager/task_manager.cpp
                               ${PROJECT_SOURCE_DIR}/src/task_manager/task.cpp)

target_link_libraries(demo PUBLIC taskmanager)

target_include_directories(taskmanager PUBLIC
                           "${PROJECT_SOURCE_DIR}/include")

target_include_directories(demo PUBLIC "${PROJECT_SOURCE_DIR}/include")
