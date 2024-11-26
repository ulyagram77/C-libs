cmake_minimum_required(VERSION 2.8) 

project(string_block-linked LANGUAGES C)

set(SOURCE_LIB ${PROJECT_NAME}.c)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})