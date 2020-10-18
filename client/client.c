#include <stdlib.h> // exit
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h> // bzero
#include <string.h> // strlen
#include <unistd.h> // write, read
#include <netdb.h> // hostent

void error(char *msg) {
  perror(msg);
  exit(0);
}

int main() {
  int sockfd, port, charlen;
  struct sockaddr_in servaddr;
  struct hostent *server;

  char buffer[256];
  port = 5717;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("Error opening socket");

  server = gethostbyname("localhost"); // ptr to hostent about host 
  if (server == NULL) {
    fprintf(stderr,"Error, no such host\n");
    exit(0);
  }

  bzero((char *) &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&servaddr.sin_addr.s_addr, server->h_length); // set servaddr.s_addr.s_addr
  servaddr.sin_port = htons(port); // set port

  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) error("Error connecting");
  bzero(buffer, 256);
  sprintf(buffer, "Hello server!");
  charlen = write(sockfd, buffer, strlen(buffer));
  if (charlen < 0) error("Error writing to socket");

  bzero(buffer, 256);
  charlen = read(sockfd, buffer, 255); // response
  if (charlen < 0) error("Error reading from socket");
  printf("%s\n", buffer);

  return 0;
}

// structure by https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html