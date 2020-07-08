cmake_minimum_required(VERSION 3.14)
project(ClientNP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(ClientNP main.cpp)
target_link_libraries(ClientNP wsock32 ws2_32)