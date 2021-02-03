#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char*message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char**argv)
{
    if(argc!=3)
    {
        error("Error on command line arguments. Fallo en la linea de argumentos");
    }

    int port_number = atoi(argv[2]);
    
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(port_number);

    
    int client = socket(AF_INET, SOCK_STREAM, 0);

    
    if(client<0)
    {
        error("Error openning socket. Error abriendo el socket.");
    }
    
    
    if(connect(client, (void*)&server_address, sizeof(server_address))!=0)
    {
        perror("Error connecting. No se pudo conectar");
    }

    char* buffer = malloc(1024);
    
    int n;

    
    n = read(client, buffer, 1024);

    
    if(n < 0)
    {
        error("ERROR reading from socket");
    }
   

    printf("%s", buffer);
    
    char message[1024];
    
    
    while(strcmp(message,"Exit")!=0 && strcmp(message,"Exit_all")!=0)
    {
        
        bzero(buffer, 1024);

        scanf("%s", message);

        if(send(client, message, strlen(message),MSG_CONFIRM)<0)
        {
            error("Error sending messages to the server. Error enviando mensajes al servidor.");
        }

        
        while(strcmp(buffer,"Exit")!=0)
        {
            bzero(buffer, 1024);
            
            n = read(client, buffer, 1024);

            if(n < 0)
            {
                error("ERROR reading from socket. Error leyendo del socket.");
            }

            strcpy(message, buffer);

            if(strcmp(buffer,"Exit")!=0)
            {
               printf("%s", buffer); 
            }
            
        }

    }

    close(client);

    return 0;

}