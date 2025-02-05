cmake_minimum_required(VERSION 3.7)
project(Server_Client)

set(CMAKE_CXX_STANDARD 11)

# Option to build the client
option(BUILD_CLIENT "Build the client executable" ON)

# Option to build the server
option(BUILD_SERVER "Build the server executable" ON)

# Add sources for the server and client
set(SERVER_SOURCES main.cpp server.cpp server.h)
set(CLIENT_SOURCES main.cpp client.cpp client.h)

# Add executable only if the corresponding option is ON
if(BUILD_SERVER)
    add_executable(Server ${SERVER_SOURCES})
    target_link_libraries(Server Threads::Threads)
endif()

if(BUILD_CLIENT)
    add_executable(Client ${CLIENT_SOURCES})
    target_link_libraries(Client Threads::Threads)
endif()

# Enable threading support
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
