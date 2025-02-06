#include <iostream>
#include "server.h"
#include "client.h"
#include "rapidjson/document.h"

int main() {
#ifdef BUILD_SERVER
    Server server;
    server.server();
#endif

#ifdef BUILD_CLIENT
    Client client;
    client.client();
#endif

    return 0;
}