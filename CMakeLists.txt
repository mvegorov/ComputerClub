cmake_minimum_required(VERSION 3.24)
project(untitled16)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled16 include/time.h include/events.h include/client.h include/table.h src/time.cpp src/events.cpp src/client.cpp src/table.cpp src/computer_club.cpp src/main.cpp src/input_validator.cpp)
