#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr1;
  addr1.sin_family = AF_INET;
  addr1.sin_port = 44004;
  addr1.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  bind(sock, & addr1, sizeof(struct sockaddr_in)); 
  struct sockaddr_in addr2;
  listen(sock, 1);
  int sockcl;
  int bu;
  sockcl =  accept(sock, &addr2, &bu);
  char buf[12];
  recv(sockcl, buf, 12, NULL);
  send(sockcl, buf, 12, NULL);
  shutdown(sock, 2);
  close(sock);
  return 0;
}
