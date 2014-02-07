#include <stdio.h>
int main() {
  int fd[2];
  size_t size;
  char string[] = "Hello, world!";
  char st[50];
  int sz = 14;
  
  printf("Ok\n");
  if (pipe(fd) == 0) {
    printf("Piped\n");
    int id = fork();
    if (id > 0)
      size = write(fd[1], string, sz);
    else {
      size = read(fd[0], st, sz);
      printf("|%s|\n", st);
    }
  }

  close(fd[0]);
  close(fd[1]);

  return 0;
}
