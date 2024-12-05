cmake_minimum_required(VERSION 2.8) 

project(merge_sort LANGUAGES C)

include_directories(../dyn_arr)
include_directories(../sort_common)

set(SOURCE_LIB ${PROJECT_NAME}.c)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})

target_link_libraries(${PROJECT_NAME} dyn_arr)
target_link_libraries(${PROJECT_NAME} sort_common)