#include <fcntl.h>
#include <stdio.h>

int main() {
  size_t size;
  char string[] = "Hello, Kitty!";
  char st[50];
  int sz = 14;
  
  int fd = open("Fifo.txt", O_RDWR);

  size = read(fd, st, sz);
  printf("Prog3 read - |%s|\n", st); 

  sleep(3);
 
  size = write(fd, string, sz);

  close(fd);
  return 0;
}
