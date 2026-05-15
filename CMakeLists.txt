cmake_minimum_required(VERSION 4.2)
project(SO2_HW2 C)

set(CMAKE_C_STANDARD 17)

add_executable(SO2_HW2 server.c
        client.c)
