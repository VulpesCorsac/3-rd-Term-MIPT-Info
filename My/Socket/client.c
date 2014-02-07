#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 44004;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  char buf[12];
  connect(sock, &addr, sizeof(struct sockaddr_in));
  send(sock, "Hello World!", 12, NULL);
  recv(sock, buf, 12, NULL);
  printf("%s", buf);
  close (sock);
  return 0;
}
