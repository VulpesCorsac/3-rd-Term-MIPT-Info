#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <curses.h>
#include <errno.h>

int w_x, w_y;
WINDOW* c_window;

char cur_msg[356];
char ln_buff[100][256];
int ln_sk;
int sck;
struct sockaddr_in srv_addr;
char * nck = NULL;

void stripws(char* s) {
    int l = strlen(s);
    while (l > 0 && (s[l-1] == 0xD || s[l-1] == 0xA || s[l-1] == ' ')) {
        l--;
        s[l] = 0;
    }
}

void prep_window() {
    clear();
    getmaxyx(c_window, w_y, w_x);
    move(w_y-2, 0);
    hline(ACS_HLINE, w_x);
    move(w_y-1, 0);
    clrtoeol();
    refresh();
    //wrefresh(c_window);
    //redrawwin(c_window);
}

void upd_window() {
    int i = ln_sk;
    int j;
    for (j = w_y-3; j>=0; j--) {
        move(j, 0);
        clrtoeol();
        printw(ln_buff[i]);
        i--;
        if (i < 0)
			i = 99;
    }
    move(w_y-1, 0);
    clrtoeol();
    printw(cur_msg);
    refresh();
}

void add_line(char* s) {
    int l = strlen(s);
    if (l > w_x)
		s[w_x] = 0;
    ln_sk++;
    if (ln_sk > 99)
		ln_sk = 0;
    strcpy(ln_buff[ln_sk], s);
}

int onCommand(char* nstr) {
    stripws(nstr);
    char msgbuff[1024];
    msgbuff[0] = 0;
    int l = 0;
    if (strcmp(nstr, "shut") == 0) {
        msgbuff[0] = 3;
        l = 10;
    } else 
		if (strcmp(nstr, "close") == 0) {
			return 0;
		} else {
			msgbuff[0] = 1;
			strcpy(msgbuff+1, nck);
			strcpy(msgbuff+40, nstr);
			l = 40 + 1 + strlen(nstr);
		}
    sendto(sck, msgbuff, l, 0, (struct sockaddr*)  &srv_addr, sizeof(struct sockaddr));
    if (msgbuff[0] == 3)
		return 0;
    return 1;
}

int main() {
    sck = socket ( AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0 );
    
    srv_addr.sin_family = AF_INET;
    if (!inet_aton("192.168.7.13", &srv_addr.sin_addr)) {
	    printf("FAIL");
    }
    srv_addr.sin_port = htons(5887);
    
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
        ///CURSES INITS HERE
    ln_sk = 0;
    int k = 0;
    for (k = 0; k < 100; k++) {
        ln_buff[k][0] = 0;
    }
    c_window = initscr();
    nodelay(c_window, true);
    cbreak();
    noecho();
    keypad(c_window, true);
    prep_window(); 

    add_line("Connecting\n");
    char reqbuff[256];
    reqbuff[0] = 2;
    sendto(sck, reqbuff, 32, 0, (struct sockaddr*)  &srv_addr, sizeof(struct sockaddr));

    while (1) {
        char* nstr = NULL;
        size_t ssz = 0;

        int c = wgetch(c_window);
        if (c != ERR) {
            if (c == KEY_BACKSPACE) {
                int l = strlen(cur_msg);
                if (l != 0) {
                    cur_msg[l-1] = 0;
                }
            } else 
				if (c == '\n') {
					if (!onCommand(cur_msg))
						break;
					char ss[512];
					sprintf(ss, "%s:%s", nck, cur_msg);
					add_line(ss);
					cur_msg[0] = 0;
				} else {
					int l = strlen(cur_msg);
					if (l < w_x-1) {
						cur_msg[l] = c;
						cur_msg[l+1] = 0;
					}
				}
            upd_window();
        }        
        
	    struct sockaddr_in ns;
	    int l = sizeof(struct sockaddr);
	    int k = recvfrom(sck, reqbuff, 160, MSG_DONTWAIT, (struct sockaddr*) &ns, &l);

        if (k > 0) {
            if (reqbuff[0] == 1) {
                add_line("Server shutdown\n");
                break;
            } else {
                add_line(reqbuff+1);
                upd_window();
            }
        } else {
            errno = 0;
        }
    }

    add_line("Connection closed \n");
    upd_window();
    
    close(sck);
    sleep(1);
    endwin();
}
