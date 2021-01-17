#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/types.h>

int main()
{
    struct sockaddr_in direccionServidor;

    direccionServidor.sin_family=AF_INET;
    direccionServidor.sin_addr.s_addr=INADDR_ANY;
    direccionServidor.sin_port=htons(8080);

    int servidor = socket(AF_INET, SOCK_STREAM, 0);

    int activado = 1;

    setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));


    if(bind(servidor, (void*)&direccionServidor, sizeof(direccionServidor))!=0)
    {
        perror("Fallo el bind");
        exit(EXIT_FAILURE);
    }

    printf("Estoy escuchando...\n");

    listen(servidor, 100);



    struct sockaddr_in direccionCliente;
    unsigned int tamañoDireccion;

    int cliente = accept(servidor, (void*)&direccionCliente, &tamañoDireccion);


    printf("Recibi una conexion en %d!!\n", cliente);

    send(cliente, "Hola NetCat", 13, 0);
    send(cliente, ":)", 3, 0);

    /*char * buffer = malloc(5);

    int bytesRecibidos = recv(cliente, buffer, 4, 0);//recv(cliente, buffer, 4, MSG_WAITALL); No recive el mensaje hasta que el buffer no este lleno

    if(bytesRecibidos < 0)
    {
        perror("Se ha desconectado");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRecibidos] = '\0';

    printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);
Esto sirve cuando sabemos el tamaño del paquete que vamos a recibir*/

 
 /*   //Si no sabemos el tamaño del paquete 
    uint32_t tamañoPaquete;
    recv(cliente, &tamañoPaquete, 4, 0);

    char*buffer = malloc(tamañoPaquete);

    recv(cliente, buffer, tamañoPaquete, MSG_WAITALL);*/

    char* buffer = malloc(256);
int n;

    while(1)
    {
        bzero(buffer, 256);
        /*int bytesRecibidos = recv(cliente, buffer, 1000,0);

        if(bytesRecibidos < 0)
        {
            perror("Se ha desconectado");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRecibidos] = '\0';
        printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);*/

        n = read(cliente, buffer, 255);

        //Error control
        if(n < 0)
        {
            perror("Error reading from socket");
        }

        printf("Here is the message: %s\n", buffer);
    }
    
    free(buffer);

    return 0;
}