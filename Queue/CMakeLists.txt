cmake_minimum_required(VERSION 3.15)

project(Queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(Queue src/main.cpp header/queue.cpp headers/queue.h)
