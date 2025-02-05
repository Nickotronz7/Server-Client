#include <iostream>
#include "server.h"
#include "client.h"
#include "rapidjson/document.h"

int main() {

    // If building the server
    #ifdef BUILD_SERVER
        Server server;
        server.server();
    #endif

    // If building the client
    #ifdef BUILD_CLIENT
        Client client;
        client.client();
    #endif

    return 0;
}
