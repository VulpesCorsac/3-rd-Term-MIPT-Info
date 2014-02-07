#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>

void main()
{
  /* struct sockaddr_in addr;
  inet_aton("192.168.7.10", &(addr.sin_addr));
  printf("%d", addr.sin_addr.s_addr);
  printf("%s",inet_ntoa(addr.sin_addr));
*/
  struct hostent *a;

  a = gethostbyname("www.wikipedia.org");
  printf("%s \n",a->h_name);
  int i=0;
  while(a->h_aliases[i]!=NULL)
    {printf("%s \n",a->h_aliases[i]); i++;}
  for(i =0; i < a->h_length; i++)
    printf("%s \n", a->h_addr_list[i]);
}
