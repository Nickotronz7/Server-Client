#include <iostream>
#include "server.h"
#include "client.h"
#include <rapidjson>

int main() {


    Server server;
    Client client;

    server.server();
    client.client();

    return 0;
}