#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
  long mytype;
  int message;
};

int main() {
  key_t key = ftok("myfile", 108);
  int msgget_res = msgget(key, IPC_CREAT | 0666);
  int res;
  struct msgbuf _msgbuf;
  
  int i;
  for (i = 6; i >= 0; i--) {
    printf("snt\n");
    if (i)
      _msgbuf.mytype = 1;
    else
      _msgbuf.mytype = 1;
    _msgbuf.message = i;
    res = msgsnd(msgget_res, &_msgbuf, sizeof(int), 0);
  }

  return 0;
}
