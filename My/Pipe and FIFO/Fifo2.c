#include <fcntl.h>
#include <stdio.h>

int main() {
  size_t size;
  char string[] = "Hello, World!";
  char st[50];
  int sz = 14;
  
  int fd = open("Fifo.txt", O_RDWR);
  
  size = write(fd, string, sz);
  
  sleep(3);

  size = read(fd, st, sz);
  printf("Prog2 read - |%s|\n", st);  

  close(fd);
  return 0;
}
