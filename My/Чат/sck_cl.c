#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

void stripws(char* s) {
    int l = strlen(s);
    while (l > 0 && (s[l-1] == 0xD || s[l-1] == 0xA || s[l-1] == ' ')) {
        l--;
        s[l] = 0;
    }
}

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
    
    char * nck = NULL;
    int a = 0;
    size_t sz = 0;
    printf("Enter your nickname :\n");

    getline(&nck, &sz, stdin);
    stripws(nck);
    if (strlen(nck) >= 30 || strlen(nck) <= 0) {
        printf("Too long\n");
        close(sck);
        exit(-1);
    }
    while (1) {
        char* nstr = NULL;
        size_t ssz = 0;
        
        getline(&nstr, &ssz, stdin);
        stripws(nstr);

        char msgbuff[256];
        msgbuff[0] = 0;
        int l = 0;
        if (strcmp(nstr, "shut") == 0) {
            msgbuff[0] = 3;
            l = 10;
        } else 
			if (strcmp(nstr, "close") == 0) {
				break;
			} else {
				msgbuff[0] = 1;
				strcpy(msgbuff+1, nck);
				strcpy(msgbuff+40, nstr);
				l = 40 + 1 + strlen(nstr);
			}
        sendto(sck, msgbuff, l, 0, (struct sockaddr*)  &srv_addr, sizeof(struct sockaddr));
        if (msgbuff[0] == 3)
			break;
    }

    printf("Connection closed \n");
    
    close(sck);
}
