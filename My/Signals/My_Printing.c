#include <signal.h>
#include <stdio.h>
int managed = 0;

void my_alarm(int nsig) {
  if (!managed)
    printf("Fail!\n");
  else
    exit(0);
}

int main() {
  int dt = 7;
  (void)signal(SIGALRM, my_alarm);
  alarm(dt);
  char S[5] = "hello";
  printf("Print \"hello\" in %d seconds\n", dt);
  char s[50];
  scanf("%s", s);
  int i;
  managed = 1;
  //  for (i = 0; i < 5; i++)
  //    printf("%c - %c\n", s[i], S[i]);
  for (i = 0; i < 5; i++)
    if (s[i] != S[i]) {
      printf("Fail");
      return 0;
    }
  printf("Ok!");
  return 0;
}
