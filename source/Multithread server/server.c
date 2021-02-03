#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>
#include <pthread.h>
#include <limits.h>

void error(const char*message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void*handle_connection(void*p_client_socket)
{
    int client_socket = *((int*)p_client_socket);

    free(p_client_socket);

    char*buffer = malloc(1024);
    char actualpath[_PC_PATH_MAX+1];

    size_t bytes_read;

    bzero(buffer, 256);

    recv(client_socket, buffer, 1024, 0);

    printf("Request. Solicitado:%s\n",buffer);

    FILE*fp = fopen(buffer, "r");

    if(fp==NULL)
    {
        send(client_socket, "Exit", 5, 0);
        close(client_socket);
        error("Error opening file");

        return NULL;
    }

    while(fgets(buffer, 1024, fp)!=NULL)
    {
        send(client_socket, buffer, 1024, 0);

        bzero(buffer, 1024);
    }

    send(client_socket, "Exit", 5, 0);

    close(client_socket);

    fclose(fp);

    printf("Closing connection\n");

    return NULL;
}

int main(int argc, char**argv)
{
    
    if(argc!=2)
    {
        perror("Fallo en la linea de argumentos.");
        exit(EXIT_FAILURE);
    }
    
    int port_number = atoi(argv[1]);
    
    struct sockaddr_in server_address;

    pid_t child_pid;

    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_port=htons(port_number);

    int server = socket(AF_INET, SOCK_STREAM, 0);

    int activate = 1;

    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &activate, sizeof(activate));

    if(bind(server, (void*)&server_address, sizeof(server_address))!=0)
    {
        perror("Fallo el bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server, 100)!=0)
    {
        error("Error listening");
    }

    printf("Listening. Escuchando...\n");

    

    struct sockaddr_in client_address;
    unsigned int address_size;

    char*buffer = malloc(1024);
    int n;

    int client;

    while(1)
    {
        
        
            client = accept(server, (void*)&client_address, &address_size);

            if(client < 0)
            {
               error("Error creating client's socket");
            }

            printf("Connection accepted from %s:%d. Conexion aceptada desde %s:%d!!\n", 
            inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), 
            inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

            send(client, "Welcome to the server!!\nType Exit to stop the connection\nType your message:\n", 78, 0);
        
            pthread_t t;

            int*pclient = malloc(sizeof(int));

            *pclient = client;

            pthread_create(&t, NULL, handle_connection, pclient);
    
    }
    
    free(buffer);

    

    if(close(server)!=0)
    {
        error("Error closing server socket. Socket server cerrado incorrectamente.");
    }

    printf("Both sockets clossed succesfully. Sockets cerrados correctamente");

    return 0;
}