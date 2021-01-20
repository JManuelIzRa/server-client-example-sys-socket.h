#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

//error function to print an error message and to finish the execution of the program
//its not necessary at all, its only for simplify and optimize
//Funcion error para imprimir todos los messages de error y para finalizar la ejecución del programa
//No es realmente necesaria pero simplifica el codigo y lo optimiza
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

    int port_number = atoi(argv[2]);//Port number to access. Número del puerto al que se desea acceder
    //We get the port number through command line argumetns. Obtenemos el numero a traves de la linea de argumentos
    
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(port_number);

    //Create a socket using int socket(int domain, int type, int protocol);
    //Creamos un socket usando la funcion int socket(int dominio, int tipo, int protocolo);
    int client = socket(AF_INET, SOCK_STREAM, 0);

    //Error control
    //Control de errores
    if(client<0)
    {
        error("Error openning socket. Error abriendo el socket.");
    }
    
    //We use at the same time connect() to get connected to the server and error control
    //Usamos la función connect() para conectarnos al servidor al mismo tiempo que hacemos el control de errores.
    if(connect(client, (void*)&server_address, sizeof(server_address))!=0)
    {
        perror("Error connecting. No se pudo conectar");
    }

    char* buffer = malloc(256);
    
    int n;

    //We obtain a message when we get connected to the server, we read it using the read() function
    //Obtenemos un mensaje cuando nos conectamos al servidor para leerlo usamos la funcion read()
    n = read(client, buffer, 255);

    //Error control
    if(n < 0)
    {
        error("ERROR reading from socket");
    }
    //End of error control

    printf("%s", buffer);
    
    char message[1024];
    
    //We do this loop to send and recieve messages until we type "Exit", then we leave the loop and get disconnected from the server
    //Hacemos este bucle para mandar y recivir mensajes hasta que escribimos "Exit", entonces saldremos del bucle y nos desconectaremos del servidor
    while(strcmp(message,"Exit")!=0 && strcmp(message,"Exit_all")!=0)
    {
        //Sending messages block
        //Bloque para mandar messages
        bzero(buffer, 256);

        scanf("%s", message);

        if(send(client, message, strlen(message),MSG_CONFIRM)<0)
        {
            error("Error sending messages to the server. Error enviando mensajes al servidor.");
        }

        //Recieving messages block
        //Bloque para recivir mensajes
        n = read(client, buffer, 255);

        //Error control
        if(n < 0)
        {
           error("ERROR reading from socket. Error leyendo del socket.");
        }
        //End of error control

        printf("%s", buffer);

    }

    //We close the socket
    //Cerramos el socket
    close(client);

    return 0;

}