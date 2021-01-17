#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//error function to print an error message and to finish the execution of the program
//its not necessary at all, its only for simplify and optimize
void error(const char*message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char**argv)
{
    int sockfd;
    int portno;//Port number to access
    int n;

    struct sockaddr_in server_address;
    struct hostent*server;

    char buffer[256];

    if(argc<3)
    {
        fprintf(stderr,"usage %s hostname port.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    portno = atoi(argv[2]);//We get the port nombre through command line arguments

    //Create a socket  socket(int domain, int type, int protocol), with other words socket(adrress family, type of socket, protocol)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Error control
    if(sockfd<0)
    {
        error("ERROR opening socket");
    }
    //End of error control
    
    server = gethostbyname(argv[1]);//We get the host name through command line arguments

    //Error control
    if(server==NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }
    //End of error control

    //bzero clears address structure
    bzero((char*)&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;

    bcopy((char*)server->h_addr_list, (char*)&server_address.sin_addr.s_addr, server->h_length);//He cambiado lo del h_addr_list

    server_address.sin_port = htons(portno);

    //We use at the same time connect() to get connected to the server and error control
    if(connect(sockfd, (struct sockaddr*)&server_address,sizeof(server_address))<0)
    {
        error("ERROR connecting");
    }

    printf("Please enter the message: ");

    bzero(buffer,256);

    fgets(buffer, 255, stdin);

    //We use write() to transfer a message to the socket
    n = write(sockfd, buffer, strlen(buffer));

    //Error control
    if(n < 0)
    {
        error("ERROR writing to socket");
    }
    //End of error control

    //We use bzero to clear the buffer
    bzero(buffer,256);

    //We use read() to recieve the answer from the server
    n = read(sockfd, buffer, 255);

    //Error control
    if(n < 0)
    {
        error("ERROR reading from socket");
    }
    //End of error control

    printf("%s\n", buffer);

    close(sockfd);

    return 0;

}