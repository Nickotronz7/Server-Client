//
// Created by nicko on 21/04/17.
//

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "client.h"

using namespace std;

void Client::client()
{
    int host_port = 1101;
    const char *host_name = "127.0.0.1";
    sockaddr_in my_addr;

    char buffer[1024];
    int bytecount;

    int hsock = socket(AF_INET, SOCK_STREAM, 0);
    if (hsock == -1)
    {
        perror("Error inicializando el socket");
        return;
    }

    int opt = 1;
    if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) ||
        (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt)) == -1))
    {
        perror("Error configurando las opciones del socket");
        close(hsock);
        return;
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(host_port);
    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = inet_addr(host_name);

    if (connect(hsock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        perror("Error conectando el socket");
        close(hsock);
        return;
    }

    // Enviar datos al servidor
    memset(buffer, 0, sizeof(buffer));
    printf("Ingrese texto para enviar al servidor (presione enter):\n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline

    if ((bytecount = send(hsock, buffer, strlen(buffer), 0)) == -1)
    {
        perror("Error enviando datos");
        close(hsock);
        return;
    }
    printf("Bytes enviados: %d\n", bytecount);

    // Recibir respuesta del servidor
    memset(buffer, 0, sizeof(buffer));
    if ((bytecount = recv(hsock, buffer, sizeof(buffer) - 1, 0)) == -1)
    {
        perror("Error recibiendo datos");
        close(hsock);
        return;
    }

    printf("Bytes recibidos: %d\nMensaje recibido: \"%s\"\n", bytecount, buffer);
    close(hsock);
}
