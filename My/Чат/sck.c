#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char talks[256][256];
struct sockaddr_in scks[256];
struct sockaddr_in scksl[256];
int sck;

void broadc(char * msg, struct in_addr exa, int issh) {
    printf("broad : %s\n", msg);
    int i;
    for (i = 0; i < 256; i++) {
        if (scksl[i].sin_port != 0 && (scksl[i].sin_addr.s_addr != exa.s_addr || issh)) {
            char msgbuff[256];
            msgbuff[0] = 0;
            strcpy(msgbuff+1, msg);
            int l = strlen(msg);
            if (issh)
				msgbuff[0] = 1;
            sendto(sck, msgbuff, l+2, 0, (struct sockaddr*)  &scksl[i], sizeof(struct sockaddr));
        }
    }
}

int main() {
    sck = socket (AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in srv_addr;
    
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(5887);
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    
    int r = bind(sck, (struct sockaddr*) &srv_addr, sizeof(struct sockaddr));
    
    int i ;
    for (i = 0; i < 256; i++) {
	    talks[i][0] = 0;
	    scks[i].sin_addr.s_addr = 0;
	    scks[i].sin_port = 0;
	    scksl[i].sin_addr.s_addr = 0;
	    scksl[i].sin_port = 0;
    }
    
    if (r < 0) {
	    printf("Failed to bind port %d\n", srv_addr.sin_port);
	    return -1;
    } else {
	    printf("Server started on port %d\n", srv_addr.sin_port);
    }
    
    int n = 10;
    while (1) {
	    char buf[161];
	    buf[160] = 0;
	
	    struct sockaddr_in ns;
	    int l = sizeof(struct sockaddr);
	    int k = recvfrom(sck, &buf, 160, 0, (struct sockaddr*) &ns, &l);
	    if (k <= 0)
			break;
	
	    int t = buf[0];		
	    if (t == 1) {
	        int nck_l = strlen(buf+1);
	        char nck[32];
	        if (nck_l > 30) {
		        printf("invalid nick received\n");
		        continue;
	        }
	        strcpy(nck, buf+1);
	        
	        int id = -1;
	        for (i = 0; i < 256; i++) {
		        if (scks[i].sin_addr.s_addr == ns.sin_addr.s_addr
		        /*&& scks[i].sin_port == ns.sin_port*/) {
		            scks[i].sin_port = ns.sin_port;
		            id = i;
		            break;
		        }
	        }
	        
	        if (id < 0)  {
		        for (i = 0; i < 256; i++) {
		            if (scks[i].sin_port == 0) {
			            scks[i] = ns;
			            id = i;
                        char buff[256];
                        sprintf(buff, "Client %s:%s appears", inet_ntoa(ns.sin_addr), nck);
                        broadc(buff, ns.sin_addr, 0);
			            break;
		            }
		        }
	        }
	        if (id < 0) {
			    printf("Message from %s is received, but there is no room left\n", nck);
			    continue;
	        }
		    if (strcmp(talks[id], nck) != 0) {
                if (talks[id][0]) {
                    char buff[256];
                    sprintf(buff, "Client %s:%s changes nick to %s", inet_ntoa(ns.sin_addr), talks[id], nck);
                    broadc(buff, ns.sin_addr, 0);
                }
                strcpy(talks[id], nck);
            }
            char msg_buff[256];
            sprintf(msg_buff, "%s:%s", nck, buf+40);
            broadc(msg_buff, ns.sin_addr, 0);

	    } else 
			if (t == 2) {
				int id = -1;
				for (i = 0; i < 256; i++) {
					if (scksl[i].sin_addr.s_addr == ns.sin_addr.s_addr) {
						scksl[i] = ns;
						id = i;
						printf("Monitor %s updated\n", inet_ntoa(ns.sin_addr));
						break;
					}
				}
				if (id < 0)
					for (i = 0; i < 256; i++) {
						if (scksl[i].sin_port == 0) {
							scksl[i] = ns;
							id = i;
							printf("Monitor %s added\n", inet_ntoa(ns.sin_addr));
							break;
						}
					}
				if (id < 0) {
					printf("Message from %s monitor is received, but there is no room left\n", inet_ntoa(ns.sin_addr));
					continue;
				}
			} else 
				if (t == 3) {
					broadc("", ns.sin_addr, 1);
					break;
				} else {
					printf("WARN : invalid packet\n");
					continue;
				}
	
	    //printf("%s\n", buf);
	    //n--;
	    //if ( n < 0) break;
    }
    
    printf("Port closed \n");
    
    close(sck);
}
