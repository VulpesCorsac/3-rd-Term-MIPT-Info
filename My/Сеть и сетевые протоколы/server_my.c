#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

struct sockaddr_in addr;
struct sockaddr client;

int recieve_all(int sockfd) {
  void* buff;
  int len;
  recv(sockfd, buff, len, 0);
  int message = *((int*) buff);
  printf("I got - %d", message);
}

int main() {
  int sd = socket(AF_UNIX, SOCK_STREAM, 0);
  addr.sin_family = AF_UNIX;
  addr.sin_port = 15000;
  addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
  bind(sd, &addr, sizeof(addr));
  listen(sd, 100);
  
  int addrlen;
  int new_sd = accept(sd, &client, &addrlen);
  recieve_all(new_sd);

  close(new_sd);
  close(sd);
  return 0;
}
