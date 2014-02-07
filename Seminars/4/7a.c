#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    size_t size;
    char name[]="aaa.fifo"; 
    
    if((fd = open(name, O_WRONLY)) < 0)
    {
        printf("Can\'t open FIFO for writting\n");
	exit(-1); 
    } 
	
    size = write(fd, "Hello, world!", 14);

    if(size != 14)
    {
        printf("Can\'t write all string to FIFO\n"); 
        exit(-1); 
    } 

    close(fd);

    return 0;
}