#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/types.h>

//error function to print an error message and to finish the execution of the program
//its not necessary at all, its only for simplify and optimize
//Funcion error para imprimir todos los mensajes de error y para finalizar la ejecución del programa
//No es realmente necesaria pero simplifica el codigo y lo optimiza
void error(const char*message)
{
    perror(message);
    exit(EXIT_FAILURE);
}


int main(int argc, char**argv)
{
    
    if(argc!=2)
    {
        perror("Fallo en la linea de argumentos.");
        exit(EXIT_FAILURE);
    }
    
    int port_number = atoi(argv[1]);//Port number which is going to be the access point. Número del puerto que será el punto de acceso
    //We get the port number through command line argumetns. Obtenemos el numero a traves de la linea de argumentos
    
    struct sockaddr_in server_address;

    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_port=htons(port_number);

    //Create a socket using int socket(int domain, int type, int protocol);
    //Creamos un socket usando la funcion int socket(int dominio, int tipo, int protocolo);
    int server = socket(AF_INET, SOCK_STREAM, 0);

    int activate = 1;

    //Using this function we set some options of the socket, here im using SO_REUSEADDR, its function is to bind the socket even though other process is using that port
    //Usando esta funcion establecemos algunas opciones al socket, aqui estoy usando SO_REUSEADDR, su funcion es enlazar el socket aunque haya otro proceso usando el puerto 
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &activate, sizeof(activate));

    //We bind the socket with the address and make the error control
    //Enlazamos el socket con la direccion y hacemos control de errores
    if(bind(server, (void*)&server_address, sizeof(server_address))!=0)
    {
        perror("Fallo el bind");
        exit(EXIT_FAILURE);
    }

    printf("Estoy escuchando...\n");

    //Using that function we make the socket passive, it means that it will be used to accept incoming connections requests
    //Their parametres are the socket and the backlog, which defines the maximum of the queue of pending connections
    //Usando esta funcion el socket se vuelve pasivo, esto significa que solo será usasda para aceptar peticiones the conexion
    //Sus parametros son el socket y un backlog, que define la cantidad maxima de peticiones de conexion pendientes en cola
    listen(server, 100);

    struct sockaddr_in client_address;
    unsigned int address_size;

    //accept() function is used to extract the first connecction request on the queue of pending connections for the listening socket
    //It creates a new connected socket without affecting the main socket wich is still listening 
    //La funcion accept() es usada para extraer la primera peticion de conexion de la cola de conexiones pendientes del socket que está escuchando
    //Crea un socket conectado nuevo sin afectar al socket principal, el cual sigue escuchando
    int client = accept(server, (void*)&client_address, &address_size);


    printf("Recibi una conexion en %d!!\n", client);


    //This block commented is an example of how to recieve messages from the client when we know the size of the package sent
    //Este bloque comentado es una ejemplo de como recivir mensajes del cliente cuando sabemos el tamaño de paquete enviado
    /*char * buffer = malloc(5);

    int bytesRecibidos = recv(client, buffer, 4, 0);//recv(client, buffer, 4, MSG_WAITALL); No recive el mensaje hasta que el buffer no este lleno

    if(bytesRecibidos < 0)
    {
        error("It get disconnected. Se ha desconectado");
    }

    buffer[bytesRecibidos] = '\0';

    printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);*/

 
    //This block commented is an example of how to recieve messages from the client when we DONT know the size of the package sent
    //Este bloque comentado es una ejemplo de como recivir mensajes del cliente cuando NO sabemos el tamaño de paquete enviado
 
 /* uint32_t package_size;
    recv(client, &package_size, 4, 0);

    char*buffer = malloc(package_size);

    recv(client, buffer, package_size, MSG_WAITALL);*/
  
    //Uncomment this if you want to use recv(). Descomenta esto si quieres usar recv()
    //uint32_t package_size; 
    //char* buffer = malloc(package_size);

    char*buffer = malloc(1024);
    int n;

    //When the client get connected we sent him this message
    //Cuando el cliente se conecta le mandamos este mensaje
    send(client, "Welcome to the server!!\nType Exit to stop the connection\nType your message:\n", 78, 0);

    //We do this loop to recieve message and send a confirmation messages until the client type "Exit", then we leave the loop and disconnect the client and the main socket
    //Hacemos este bucle para recibir mensaje y mandar mensajes de confirmacion hasta que el cliente escribe "Exit", entonces saldremos del bucle y se desconectara el socket cliente y el main.
    while(strcmp(buffer,"Exit")!=0)
    {
        bzero(buffer, 256);
        
        /*
        recv(client, buffer, package_size, 0);
        */

       
        n = read(client, buffer, 255);

        //Error control
        if(n < 0)
        {
            error("Error reading from socket. Error leyendo del socket");
        }
        

        printf("This is the message. Este es el mensaje: %s\n", buffer);

        if(strcmp(buffer,"Exit")==0)
        {
           n = write(client, "Ending connection. Finalizando conexion...\n",45);
        }
        else
        {
            n = write(client, "Received. Recibido\n", 21);
        }

        if(n < 0)
        {
            error("Error writing to the socket· Error escribiendo al socket");
        }

        //send(client,"Recibido\n",11,0);
    }
    
    free(buffer);

    if(close(client)!=0)
    {
        error("Error closing client socket. Socket client cerrado incorrectamente.");
    }

    if(close(server)!=0)
    {
        error("Error closing server socket. Socket server cerrado incorrectamente.");
    }

    printf("Both sockets clossed succesfully. Sockets cerrados correctamente");

    return 0;
}