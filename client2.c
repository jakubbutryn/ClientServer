#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
perror(msg);
exit(1); 
}
int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno; // defines ints
socklen_t clilen; 
char buffer[256];
struct sockaddr_in serv_addr, cli_addr; 
struct hostent *server; 
int n;
if (argc < 2) {
fprintf(stderr,"ERROR, no port provided\n");
exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0); 
if (sockfd < 0)
error("ERROR opening socket"); 
server = gethostbyname(argv[1]);
if (server == NULL) {
fprintf(stderr,"ERROR, no such host\n");
exit(0); // exit main() function
}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET; // define address family (IPv4)

bcopy((char *)server->h_addr,
(char *)&serv_addr.sin_addr.s_addr,
server->h_length);


portno = atoi(argv[2]); 
serv_addr.sin_port = htons(portno); 
if (bind(sockfd, (struct sockaddr *) &serv_addr,
sizeof(serv_addr)) < 0)
error("ERROR on binding"); 
listen(sockfd,5); 
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd,
(struct sockaddr *) &cli_addr,
&clilen); 
if (newsockfd < 0)
error("ERROR on accept");
bzero(buffer,256);
n = read(newsockfd,buffer,255); 
if (n < 0) error("ERROR reading from socket");
printf("Here is the message: %s\n",buffer); 
n = write(newsockfd,"I got your message",18); 
if (n < 0) error("ERROR writing to socket"); //
close(newsockfd); 
close(sockfd); 
return 0;
}

