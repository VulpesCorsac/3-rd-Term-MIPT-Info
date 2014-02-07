#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int a = 0;

int main() {
  fork();
  a++;
  printf("a = %d\n", a);
  return 0;
}
