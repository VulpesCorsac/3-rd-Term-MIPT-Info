#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct UdpHeader
{
    u_short src_port;
    u_short targ_port;
    u_short length;
    u_short checksum;
};

char message[] = "Hello there!\n";
char msgbuf[1024];

int main()
{
    int sock;
    struct sockaddr_in addr;
    struct UdpHeader header;
    
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    header.targ_port = htons(3425);
    header.length = htons(sizeof(header)+sizeof(message));
    header.checksum = 0;
    
    memcpy((void *)msgbuf, (void *)&header, sizeof(header));
    memcpy((void *)(msgbuf+sizeof(header)), (void *)message, sizeof(message));
    
    sendto(sock, msgbuf, sizeof(header)+sizeof(message), 0,
           (struct sockaddr *)&addr, sizeof(addr));
    
    close(sock);
    
    return 0;
}