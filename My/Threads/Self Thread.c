#include <stdio.h>
#include <pthread.h>

int main() {
  int key = 0;
  pthread_t a = pthread_self();
  printf("Thread = %ld\n", a);
  return 0;
}

// compile = gcc 1.c -lpthread -o 1
