cmake_minimum_required(VERSION 2.8) 

project(tree_sort LANGUAGES C)

include_directories(../dyn_arr)

set(SOURCE_LIB ${PROJECT_NAME}.c)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})

target_link_libraries(${PROJECT_NAME} dyn_arr)