cmake_minimum_required(VERSION 3.7)
project(Server_Client)

set(CMAKE_CXX_STANDARD 11)

# Options to enable/disable server and client builds
option(BUILD_SERVER "Build the server executable" ON)
option(BUILD_CLIENT "Build the client executable" ON)

set(SOURCE_FILES main.cpp)
set(SERVER_SOURCES server.cpp server.h ${SOURCE_FILES})
set(CLIENT_SOURCES client.cpp client.h ${SOURCE_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Build Server
if (BUILD_SERVER)
    add_executable(Server ${SERVER_SOURCES})
    target_link_libraries(Server Threads::Threads)
    target_compile_definitions(Server PRIVATE BUILD_SERVER)
endif()

# Build Client
if (BUILD_CLIENT)
    add_executable(Client ${CLIENT_SOURCES})
    target_link_libraries(Client Threads::Threads)
    target_compile_definitions(Client PRIVATE BUILD_CLIENT)
endif()
