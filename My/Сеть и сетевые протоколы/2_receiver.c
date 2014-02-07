#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>


int main()
{
    int sock;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    
    while(1)
    {
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
        buf[bytes_read] = '\0';
        printf(buf);
    }
    
    return 0;
}
