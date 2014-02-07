#include <stdio.h>
int main() {
  int fd1[2], fd2[2];
  size_t size;
  char string1[] = "Hello, World?";
  char string2[] = "hello, world!";
  char st1[50], st2[50];
  int sz = 14;
  
 if(pipe(fd1) != 0)
   printf("Bad1\n");
 if(pipe(fd2) != 0)
   printf("Bad2\n");
 int id = fork();
 if (id < 0)
   printf("Bad");
 if (id > 0) {
   size = read(fd1[0], st1, sz);
   printf("Parent read - |%s|\n", st1);

   size = write(fd2[1], string2, sz);
 } else {
   size = write(fd1[1], string1, sz);

   size = read(fd2[0], st2, sz);
   printf("Child read - |%s|\n", st2);
 }

  close(fd1[0]);
  close(fd1[1]);
  close(fd2[0]);
  close(fd2[1]);

  return 0;
}
