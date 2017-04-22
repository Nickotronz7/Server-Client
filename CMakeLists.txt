cmake_minimum_required(VERSION 3.7)
project(Server_Client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp server.cpp server.h client.cpp client.h)
add_executable(Server_Client ${SOURCE_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Server_Client Threads::Threads)