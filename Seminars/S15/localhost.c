#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>  
#include <unistd.h>  

char as[20];

int main(int argc, char *argv[]) {
  gethostname(as, 20);
  printf("%s", as);
  exit(EXIT_SUCCESS);
}
