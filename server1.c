#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{

int sockfd, portno, n; // define ints
int sockfd2, portno2, n2; // define ints

struct sockaddr_in serv_addr; // define structs
struct sockaddr_in serv_addr2; // define structs
struct sockaddr_in cli_addr; // defines structures
socklen_t clilen; //size of address
int newsockfd; // defines ints

char buffer[256]; // define buffer
char buffer2[256]; // define buffer

if (argc < 3) {
fprintf(stderr,"usage %s hostname port\n", argv[0]);
exit(0); // exit main() function
}

portno = atoi(argv[1]); // get port number
portno2 = atoi(argv[2]); // get port number

//Pierwszy Socket
sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket
if (sockfd < 0)
error("ERROR opening socket"); // if socket creation failed

bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET; // define address family (IPv4)
serv_addr.sin_addr.s_addr = INADDR_ANY; // bind IP addresses
serv_addr.sin_port = htons(portno); // assign port

//if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
//error("ERROR connecting"); // if connection failed

//Przesyl wiadomosci 
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
strcpy(buffer2,buffer);
if (n < 0) error("ERROR reading from socket"); // if error
printf("Here is the message: %s\n",buffer); // show the message
n = write(newsockfd,"I got your message",18); // notify
if (n < 0) error("ERROR writing to socket"); //
close(newsockfd); // close connection socket
close(sockfd); // close listening socket

//Drugi Socket
sockfd2 = socket(AF_INET, SOCK_STREAM, 0); // create socket
if (sockfd2 < 0)
error("ERROR opening socket 2"); // if socket creation failed
bzero((char *) &serv_addr2, sizeof(serv_addr2));
serv_addr2.sin_family = AF_INET; // define address family (IPv4)
serv_addr2.sin_port = htons(portno2); // assign port

if (connect(sockfd2,(struct sockaddr *) &serv_addr2,sizeof(serv_addr2)) < 0)
error("ERROR connecting 2"); // if connection failed

n2 = write(sockfd2,buffer2,strlen(buffer2)); // write the msg to socket
if (n2 < 0)
error("ERROR writing to socket"); // writing failed
bzero(buffer2,256); // if writing succeed, zero the buffer
n2 = read(sockfd2,buffer2,255); // read from socket into buffer
if (n2 < 0)
error("ERROR reading from socket"); // if reading failed
printf("%s\n",buffer2); // print buffer
close(sockfd2); // close socket

return 0; // exit main() function
}
