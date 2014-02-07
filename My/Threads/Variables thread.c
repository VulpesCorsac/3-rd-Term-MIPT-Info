#include <stdio.h>
#include <pthread.h>

int key = 0;

void* my_thread(void *params) {
  printf("My thread = %ld, key = %d\n", pthread_self(), key);
  key++;
  pthread_exit(NULL);
}

int main() {
  pthread_t my_pthread;
  key++;
  if(pthread_create(&my_pthread, NULL, &my_thread, NULL))
    return -1;
  if(pthread_join(my_pthread, NULL))
    return -2;
  printf("Main thread = %ld, key = %d\n", pthread_self(), key);
  return 0;
}

// compile with "gcc 1.c -lpthread -o 1"
