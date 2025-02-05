//
// Created by nicko on 21/04/17.
//
#include <fstream>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "server.h"

using namespace std;

void *socketHandler(void *);
sockaddr_in sadr;

void Server::server()
{
    host_port = 1101;
    pthread_t thread_id = 0;

    hsock = socket(AF_INET, SOCK_STREAM, 0);
    if (hsock == -1)
    {
        perror("Error iniciando el socket");
        return;
    }

    int opt = 1;
    if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) ||
        (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt)) == -1))
    {
        perror("Error al configurar las opciones del socket");
        close(hsock);
        return;
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(host_port);
    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(hsock, (sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        perror("Error uniendo al socket, asegúrese de que el puerto está libre");
        close(hsock);
        return;
    }

    if (listen(hsock, 10) == -1)
    {
        perror("Error al escuchar");
        close(hsock);
        return;
    }

    addr_size = sizeof(sockaddr_in);

    while (true)
    {
        printf("Esperando una conexión en el puerto %i...\n", host_port);
        csock = new int;
        if ((*csock = accept(hsock, (sockaddr *)&sadr, &addr_size)) != -1)
        {
            printf("---------------------\nConexión recibida de %s\n", inet_ntoa(sadr.sin_addr));
            pthread_create(&thread_id, nullptr, &socketHandler, (void *)csock);
            pthread_detach(thread_id);
        }
        else
        {
            perror("Error al aceptar conexión");
            delete csock;
        }
    }

    close(hsock);
}

void *socketHandler(void *lp)
{
    int *csock = (int *)lp;
    const int buffer_len = 1024;
    char buffer[buffer_len];
    int bytecount;

    memset(buffer, 0, buffer_len);

    if ((bytecount = recv(*csock, buffer, buffer_len - 1, 0)) == -1)
    {
        perror("Error al recibir datos");
    }
    else
    {
        printf("Bytes recibidos: %d\nMensaje recibido: \"%s\"\nDe: %s\n", bytecount, buffer, inet_ntoa(sadr.sin_addr));

        strcat(buffer, " SERVER ECHO");
        if ((bytecount = send(*csock, buffer, strlen(buffer), 0)) == -1)
        {
            perror("Error al enviar datos");
        }
        else
        {
            printf("Bytes enviados: %d\n", bytecount);
        }
    }

    close(*csock);
    delete csock;
    return nullptr;
}
