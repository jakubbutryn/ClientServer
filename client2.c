#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
// define function that deals with errors
void error(const char *msg)
{
perror(msg); // print error msg
exit(1); // exit the main() function
}
int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno; // defines ints
socklen_t clilen; //size of address
char buffer[256]; // buffer
struct sockaddr_in serv_addr, cli_addr; // defines structures
struct hostent *server; // defecines host address struct
int n;
if (argc < 2) {
fprintf(stderr,"ERROR, no port provided\n"); // deal with wrong port
exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0); // makes a socket
if (sockfd < 0)
error("ERROR opening socket"); // if socket creation failed
server = gethostbyname(argv[1]); // get server address
if (server == NULL) {
fprintf(stderr,"ERROR, no such host\n"); // if server address is not proper
exit(0); // exit main() function
}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET; // define address family (IPv4)

bcopy((char *)server->h_addr,
(char *)&serv_addr.sin_addr.s_addr,
server->h_length); // copy byte data


portno = atoi(argv[2]); // get port number
serv_addr.sin_port = htons(portno); // set port number
if (bind(sockfd, (struct sockaddr *) &serv_addr,
sizeof(serv_addr)) < 0)
error("ERROR on binding"); // error while binding socket
listen(sockfd,5); // listen on created socket
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd,
(struct sockaddr *) &cli_addr,
&clilen); // creates new socket for first incoming connection
if (newsockfd < 0)
error("ERROR on accept"); // error while creating socket
bzero(buffer,256);
n = read(newsockfd,buffer,255); // read from connection socket
if (n < 0) error("ERROR reading from socket"); // if error
printf("Here is the message: %s\n",buffer); // show the message
n = write(newsockfd,"I got your message",18); // notify
if (n < 0) error("ERROR writing to socket"); //
close(newsockfd); // close connection socket
close(sockfd); // close listening socket
return 0;
}

