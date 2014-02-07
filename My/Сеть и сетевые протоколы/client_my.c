#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int send_all(int s, char *buf, int len, int flags) {
  int total = 0;
  int n;
  while (total < len) {
    n = send(s, buf+total, len-total, flags);
    if (n == -1)
      break;
    total += n;
  }
  return (n == -1 ? -1 : total);
}

int main() {
  int sd = socket(AF_UNIX, SOCK_STREAM, 0);
  
  send_all()
  close(sd);
  return 0;
}
