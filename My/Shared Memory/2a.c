#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_SIZE 1738

int main()
{ 
    int shmid;
    int fd; 
    int size;
    int i;
    char pathname[] = "2a.c";
    char string[FILE_SIZE];
    char *shstring;
    key_t key; 
    
    if ((fd = open("2a.c", O_RDONLY)) < 0)                                    
    {                                                                           
        printf("Can\'t open file\n");                                           
        exit(-1);                                                               
    }  
    
    size = read(fd, string, FILE_SIZE);
    if (size != FILE_SIZE)                                                             
    {                                                                           
        printf("Can\'t read all string\n");                                     
        exit(-1);                                                               
    }     
    
    if(close(fd) < 0)                                      
	printf("Can\'t close file\n");

    if((key = ftok(pathname,0)) < 0)
    {
	printf("Can\'t generate key\n");
	exit(-1);
    }
    
    if((shmid = shmget(key, FILE_SIZE*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
	printf("Can\'t create shared memory\n");                            
	exit(-1);
    } 
 
    if((shstring = (char *)shmat(shmid, NULL, 0)) == (char *)(-1))
    {
	printf("Can't attach shared memory\n");
	exit(-1);
    } 
 
    for (i = 0; i < FILE_SIZE; i++)
	shstring[i] = string[i];
	
    if(shmdt(shstring) < 0)
    {
	printf("Can't detach shared memory\n");
	exit(-1);
    }
    
    return 0;
}