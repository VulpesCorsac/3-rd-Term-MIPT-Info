#include <sys/stat.h>
#include <unistd.h>

int main() {
  mknod("Fifo.txt", 0666, 0);
  //  execvp("./fifo2", NULL);
  //  execvp("./fifo3", NULL);
  return 0;
}
