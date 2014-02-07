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
  read(fd, (void*) st, size);
  int i;
  for (i = 0; i < number; i++) {
    printf("i = %d, f1 = %lf, f2 = %lf\n", i, st[i].f1, st[i].f2);
  }
  return 0;
}
