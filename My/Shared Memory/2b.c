#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>

#define FILE_SIZE 1738

int main()
{ 
    int shmid; 
    char pathname[] = "2a.c";
    char *shstring;
    key_t key; 
    
    if((key = ftok(pathname,0)) < 0)
    {
	printf("Can\'t generate key\n");
	exit(-1);
    }
    
    if((shmid = shmget(key, FILE_SIZE*sizeof(char), NULL)) < 0)
    {
	printf("Can\'t create shared memory\n");                            
	exit(-1);
    } 
 
    if((shstring = (char *)shmat(shmid, NULL, 0)) == (char *)(-1))
    {
	printf("Can't attach shared memory\n");
	exit(-1);
    } 
 
    printf("%s\n", shstring);
	
    if(shmdt(shstring) < 0)
    {
	printf("Can't detach shared memory\n");
	exit(-1);
    }
    
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}