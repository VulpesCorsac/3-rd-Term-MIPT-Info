#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
  key_t key = ftok("myfile", 108);
  int sem = semget(key, 1, IPC_CREAT | 0666);
  struct sembuf _sembuf;
  _sembuf.sem_num = 0;
  _sembuf.sem_op = 1;
  _sembuf.sem_flg = 0;
  int res = semop(sem, &_sembuf, 1);
  return 0;
}
