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

int sockfd, portno, n;
int sockfd2, portno2, n2; 

struct sockaddr_in serv_addr;
struct sockaddr_in serv_addr2; 
struct hostent *server; 

char buffer[256]; 
char buffer2[256]; 

if (argc < 4) {
fprintf(stderr,"usage %s hostname port\n", argv[0]);
exit(0); // exit main() function
}

portno = atoi(argv[2]); 
portno2 = atoi(argv[3]); 

sockfd = socket(AF_INET, SOCK_STREAM, 0); 
if (sockfd < 0)
error("ERROR opening socket"); 
server = gethostbyname(argv[1]);
if (server == NULL) {
fprintf(stderr,"ERROR, no such host\n"); r
exit(0); // exit main() function
}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET; 
bcopy((char *)server->h_addr,
(char *)&serv_addr.sin_addr.s_addr,
server->h_length); /
serv_addr.sin_port = htons(portno); 
if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
error("ERROR connecting"); 
printf("Please enter the message: "); 
bzero(buffer,256); // 
fgets(buffer,255, stdin);
strcpy(buffer2,buffer);
n = write(sockfd,buffer,strlen(buffer)); 
if (n < 0)
error("ERROR writing to socket"); 
bzero(buffer,256); 
n = read(sockfd,buffer,255); 
if (n < 0)
error("ERROR reading from socket");
printf("%s\n",buffer); 
close(sockfd); 

sockfd2 = socket(AF_INET, SOCK_STREAM, 0); 
if (sockfd2 < 0)
error("ERROR opening socket 2"); 
if (server == NULL) {
fprintf(stderr,"ERROR, no such host\n"); 
exit(0); // exit main() function
}
bzero((char *) &serv_addr2, sizeof(serv_addr2));
serv_addr2.sin_family = AF_INET; // define address family (IPv4)
bcopy((char *)server->h_addr,
(char *)&serv_addr2.sin_addr.s_addr,
server->h_length); 
serv_addr2.sin_port = htons(portno2); 
if (connect(sockfd2,(struct sockaddr2 *) &serv_addr2,sizeof(serv_addr2)) < 0)
error("ERROR connecting"); 
//printf("Please enter the message: ");
//bzero(buffer2,256); 
//fgets(buffer2,255,stdin); 
n2 = write(sockfd2,buffer2,strlen(buffer2)); 
if (n2 < 0)
error("ERROR writing to socket");
bzero(buffer2,256);
n2 = read(sockfd2,buffer2,255); 
if (n2 < 0)
error("ERROR reading from socket"); 
printf("%s\n",buffer2); 
close(sockfd2);


return 0; 
}
