#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char*message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char**argv)
{
    int sockfd;
    int newsockfd;
    int portno;

    socklen_t clilen;

    char buffer[256];

    struct sockaddr_in serv_addr;

    struct sockaddr_in cli_addr;

    int n;

    //Error control for command line arguments
    if(argc<2)
    {
        fprintf(stderr,"ERROR, no port provided\nWrite something like %s 20001",argv[0]);
        exit(EXIT_FAILURE);
    }

    //Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        error("Error opening the socket");
    }

    printf("Socket successfully created..\n");

    //Clear address structure
    bzero(&serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    //Setup the host_addr structure for use in bind call
    //Server byte order
    serv_addr.sin_family = AF_INET;

    //automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //convert short integer value for port must be converted into network byte order
    serv_addr.sin_port = htons(portno);
   
    //bind() passes file descriptor, the adress structure and the length of the adress structure

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))!=0)
    {
        error("Error on binding.");
    }

    //The listen() function tells the socket to listen to the incoming connections
    //it places all incoming connection into a backlog queue, the second parameter of the function set its maximum

    if(listen(sockfd, 5)!=0)
    {
        error("Error listening.");
    }

    printf("Server listening..\n"); 

    clilen = sizeof(cli_addr);

    //The accept() function will write the connecting client's address info into the address structure.´
    //The accept() function returns a new socket file descriptor for the accepted connection, so the original ssocket can continue to be used for accepting new connections

    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);

    if(newsockfd < 0)
    {
    error("Error on accept");
    }

    printf("Server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));


    while (1)
    {
        

        //The send() function send the 13 bytes of the string to the new socket
        send(newsockfd, "Hello World!!\n", 13, 0);

        //bzero() function to clear the buffer
        bzero(buffer, 256);

        //read() function to recieve the message sent by the client
        n = read(newsockfd, buffer, 255);

        //Error control
        if(n < 0)
        {
            error("Error reading from socket");
        }

        printf("Here is the message: %s\n", buffer);

        close(newsockfd);

    }
    
    close(sockfd);

    return 0;



}