#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd[2]; 
    size_t size;
    char string[] = "Hello, world!";
    char resstring[14]; 

    if(pipe(fd) < 0)
    {
	printf("Can\'t create pipe\n");
	exit(-1); 
    } 

    size = write(fd[1], string, 14);

    if(size != 14)
    {
	printf("Can\'t write all string\n"); 
	exit(-1); 
    } 

    size = read(fd[0], resstring, 14);

    if(size < 0)
    {
	printf("Can\'t read string\n"); 
	exit(-1); 
    } 

    printf("%s\n",resstring);

    if(close(fd[0]) < 0)
    { 
	printf("Can\'t close input stream\n");
    }

    if(close(fd[1]) < 0)
    { 
	printf("Can\'t close output stream\n");
    }

    return 0;
}