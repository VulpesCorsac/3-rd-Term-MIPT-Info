#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

int main() {
    int sck = socket ( AF_INET, SOCK_DGRAM, 0 );
    
    struct sockaddr_in srv_addr;
    
    srv_addr.sin_family = AF_INET;
    if (!inet_aton("192.168.7.13", &srv_addr.sin_addr)) {
	    printf("FAIL");
    }
    //srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(5887);
    //srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    printf("Connecting..\n");
    char reqbuff[256];
    reqbuff[0] = 2;
    sendto(sck, reqbuff, 32, 0, (struct sockaddr*)  &srv_addr, sizeof(struct sockaddr));

    while (1) {
	    char buf[161];
	    buf[160] = 0;
	    struct sockaddr_in ns;
	    int l = sizeof(struct sockaddr);
	    int k = recvfrom(sck, &buf, 160, 0, (struct sockaddr*) &ns, &l);
        if (k <= 0)
			break;
        if (buf[0] == 1) {
            printf("Grateful server shutdown\n");
            break;
        }
        printf("%s\n", buf+1);
    }

    printf("Connection closed \n");
    
    close(sck);
}
