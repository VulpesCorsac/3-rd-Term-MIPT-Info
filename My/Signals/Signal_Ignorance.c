/* Программа с пользовательской обработкой сигнала SIGINT */
#include <signal.h>
#include <stdio.h>
/* Функция my_handler - пользовательский обработчик сигнала */
void my_handler(int nsig){
  printf("Receive signal %d, CTRL-C pressed\n");
}

int main(void){
  /* Выставляем реакцию процесса на сигнал SIGINT */
  (void)signal(SIGINT, my_handler);
  /*Начиная с этого места, процесс будет печатать сообщение о возникновении сигнала SIGINT */
  while(1);
  return 0;
} 
