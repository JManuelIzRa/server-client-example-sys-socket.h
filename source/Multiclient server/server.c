#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>

int turn_off_signal_recieved = 0;


//error function to print an error message and to finish the execution of the program
//its not necessary at all, its only for simplify and optimize
//Funcion error para imprimir todos los mensajes de error y para finalizar la ejecución del programa
//No es realmente necesaria pero simplifica el codigo y lo optimiza
void error(const char*message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void signalHandler(int signal)
{
    printf("Recieved signal to turn off the server. Señal para apagar el servidor recibida.\n");

    turn_off_signal_recieved = 1;
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

    pid_t child_pid;

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


    //Using that function we make the socket passive, it means that it will be used to accept incoming connections requests
    //Their parametres are the socket and the backlog, which defines the maximum of the queue of pending connections
    //Usando esta funcion el socket se vuelve pasivo, esto significa que solo será usasda para aceptar peticiones the conexion
    //Sus parametros son el socket y un backlog, que define la cantidad maxima de peticiones de conexion pendientes en cola
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

    signal(SIGUSR1, signalHandler);


    //We do this loop to recieve message and send a confirmation messages until the client type "Exit", then we leave the loop and disconnect the client and the main socket
    //Hacemos este bucle para recibir mensaje y mandar mensajes de confirmacion hasta que el cliente escribe "Exit", entonces saldremos del bucle y se desconectara el socket cliente y el main.
    while(turn_off_signal_recieved == 0)
    {
        
        
            //accept() function is used to extract the first connecction request on the queue of pending connections for the listening socket
            //It creates a new connected socket without affecting the main socket wich is still listening 
            //La funcion accept() es usada para extraer la primera peticion de conexion de la cola de conexiones pendientes del socket que está escuchando
            //Crea un socket conectado nuevo sin afectar al socket principal, el cual sigue escuchando
            client = accept(server, (void*)&client_address, &address_size);

            if(client < 0)
            {
               error("Error creating client's socket");
            }

            printf("Connection accepted from %s:%d. Conexion aceptada desde %s:%d!!\n", 
            inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), 
            inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

            //When the client get connected we sent him this message
            //Cuando el cliente se conecta le mandamos este mensaje
            send(client, "Welcome to the server!!\nType Exit to stop the connection\nType your message:\n", 78, 0);
        
            if((child_pid = fork())==0)
            {
                //close(server);

                while(1)
                {
                    bzero(buffer, 256);

                    recv(client, buffer, 1024, 0);

                    printf("This is the message. Este es el mensaje: %s\n", buffer);

                    if(strcmp(buffer,"Exit")==0 || strcmp(buffer,"Exit_all")==0)
                    {
                        n = write(client, "Ending connection. Finalizando conexion...\n",45);
                    
                        if(close(client)!=0)
                        {
                            error("Error closing client socket. Socket client cerrado incorrectamente.");
                        }
                    
                        if(strcmp(buffer,"Exit_all")==0)
                        {
                           kill(getppid(),SIGUSR1);
                        }
                    
                        exit(EXIT_SUCCESS);

                    }
                    else
                    {
                        n = write(client, "Received. Recibido\n", 21);
                    }

                    if(n < 0)
                    {
                        error("Error writing to the socket· Error escribiendo al socket");
                    }
                }
            }
            else if(child_pid == -1)
            {
                error("Fork error.");
        
            }
        
        if(turn_off_signal_recieved==1)
        {
            kill(child_pid, SIGKILL);
        }
    
    }
    
    free(buffer);

    

    if(close(server)!=0)
    {
        error("Error closing server socket. Socket server cerrado incorrectamente.");
    }

    printf("Both sockets clossed succesfully. Sockets cerrados correctamente");

    return 0;
}