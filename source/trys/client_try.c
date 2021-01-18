#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char**argv)
{
    if(argc!=3)
    {
        perror("Fallo en la linea de argumentos");
        exit(EXIT_FAILURE);
    }

    int port_number = atoi(argv[2]);
    
    struct sockaddr_in direccionServidor;

    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = inet_addr(argv[1]);
    direccionServidor.sin_port = htons(port_number);

    int cliente = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(cliente, (void*)&direccionServidor, sizeof(direccionServidor))!=0)
    {
        perror("No se pudo conectar");
        exit(EXIT_FAILURE);
    }

    char* buffer = malloc(256);
    
    int n;

    n = read(cliente, buffer, 255);

    //Error control
    if(n < 0)
    {
        perror("ERROR reading from socket");
    }
    //End of error control

    printf("%s", buffer);

    while(1)
    {
        char mensaje[1000];

        scanf("%s", mensaje);

        send(cliente, mensaje, strlen(mensaje),0);
    }

    return 0;

}