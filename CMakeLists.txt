cmake_minimum_required(VERSION 4.2)
project(SO2_HW2 C)

set(CMAKE_C_STANDARD 17)

add_executable(server server.c
        server.h)
add_executable(client client.c
        client.h)
