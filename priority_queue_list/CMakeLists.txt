cmake_minimum_required(VERSION 2.8) 

project(priority_queue_list LANGUAGES C)

include_directories(../linked_list)

set(SOURCE_LIB ${PROJECT_NAME}.c)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})

target_link_libraries(${PROJECT_NAME} linked_list)