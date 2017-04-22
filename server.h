//
// Created by nicko on 21/04/17.
//

#ifndef SERVER_CLIENT_SERVER_H
#define SERVER_CLIENT_SERVER_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <malloc.h>

class Server
{
public:
    void server();

private:
    int host_port;

    struct sockaddr_in my_addr;

    int hsock;
    int * p_int ;
    int err;

    socklen_t addr_size = 0;
    int* csock;
};

#endif //SERVER_CLIENT_SERVER_H
