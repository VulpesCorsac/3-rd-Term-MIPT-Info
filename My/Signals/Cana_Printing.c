#include <unistd.h>
#include <signal.h>
#include "stdio.h"

void onAlarm(int sig)
{
    printf("\nSo slow...\n");
    exit(-1);
}

int main(void)
{
    const char* sToType = "Example string";
    
    signal(SIGALRM, onAlarm);
    
    alarm(2);
    
    printf("Type : \n");
    printf("%s\n", sToType);
    
    char* st = NULL;
    size_t  stl = 0;
    
    getline(&st, &stl, stdin);
    
    int isWin = 1;
    int i =0;
    for (i = 0; i < strlen(sToType); i++)
    {
	if (sToType[i] != st[i])
	{
	    isWin = 0;
	    break;
	}
    }
    
    if (isWin)
    {
        printf("You win!\n");
    } else {
	printf("Wrong!\n");
    }
    free(st);
} 
