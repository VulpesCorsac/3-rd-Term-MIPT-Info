#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv) {

  int mem_size = 3;
  key_t key = ftok("shared.mem", 108);
  int shmget_result = shmget(key, mem_size, 0666 | IPC_CREAT | IPC_EXCL);
  int f = 1;
  if (errno == EEXIST) {
    shmget_result = shmget(key, mem_size, 0);
    f = 0;
  }
  if (shmget_result == -1)
    return -1;
  char *ch = shmat(shmget_result, 0, 0);
  if (f)
    ch[0] = ch[1] = ch[2] = 0;

  ch[0]++;
  ch[2]++;
  
  printf("%d %d %d\n", (int) ch[0], (int) ch[1], (int) ch[2]);

  if (shmdt(ch) != 0)
    return -2;

  return 0;
}
