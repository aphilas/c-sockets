#include <stdlib.h> 
#include <stdio.h>  
#include <sys/types.h>
#include <strings.h> // bzero
#include <unistd.h> // write, read
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in

void error(char *msg) {
  perror(msg);
  exit(1);
}

int main(void) {
  int sockfd, connfd, port, clilen, charlen;
  char buffer[256]; // read chars from connection
  struct sockaddr_in servaddr, cliaddr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_UNIX, SOCK_DGRAM
  bzero((char *) &servaddr, sizeof(servaddr)); // initialize servaddr to zeros ***
  port = 5717;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port); // convert to network byte order
  servaddr.sin_addr.s_addr = INADDR_ANY; // IP addr of host

  if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) error("Error on binding"); // cast sockaddr_in to sockaddr
  listen(sockfd, 5); // int waitconn

  clilen = sizeof(cliaddr);
  connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen); // blocks

  bzero(buffer, 256);
  charlen = read(connfd, buffer, 255); // blocks; attempts to read 255 bytes before EoF
  if (charlen < 0) error("Error reading from socket");
  printf("Client says: %s\n", buffer);

  charlen = write(connfd, "Message received", 17);
  if (charlen < 0) error("Error writing to socket");

  return 0;
}

// structure by https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html