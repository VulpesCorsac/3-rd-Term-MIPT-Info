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
  long type;
  struct msgbuf _msgbuf;
  int msg = 0;

  while (1) {
    printf("rcv");
    res = msgrcv(msgget_res, &_msgbuf, sizeof(int), type, 0);
    printf("d\n");
    msg++;
    //    if (!type)
    //  break;
    printf("Msg_num = %d, msg = %d\n", msg, _msgbuf.message);
  }
  return 0;
}
