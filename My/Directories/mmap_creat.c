#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

struct A {
  double f1;
  double f2;
};

int main(int argc, char** argv) {
  int fd;
  int number = 10;
  size_t size = number*sizeof(struct A);
  fd = open("temp.dat", O_RDWR | O_CREAT, 0666);
  struct A* st = (struct A*) malloc(size);
  write(fd, (void*)st, size);
  st = (struct A*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);
  int i;
  for (i = 0; i < number; i++) {
    st[i].f1 = i;
    st[i].f2 = 2*i;
  }
  munmap(st, size);

  return 0;
}
