cmake_minimum_required(VERSION 3.17)
project(PostfixInfixStack)

set(CMAKE_CXX_STANDARD 14)

add_executable(PostfixInfixStack main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/infix.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


