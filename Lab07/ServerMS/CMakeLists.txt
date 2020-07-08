cmake_minimum_required(VERSION 3.14)
project(ServerMS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(ServerMS main.cpp)
target_link_libraries(ServerMS wsock32 ws2_32)