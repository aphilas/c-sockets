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
