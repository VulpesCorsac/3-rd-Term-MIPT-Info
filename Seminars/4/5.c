#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd1[2], fd2[2]; 
    size_t size;
    char *string;
    pid_t pid;
    
    if(pipe(fd1) < 0)
    {
	printf("Can\'t create pipe\n");
	exit(-1); 
    } 
    
    if(pipe(fd2) < 0)                                                           
    {                                                                           
        printf("Can\'t create pipe\n");                                         
	exit(-1);                                                               
    } 
    
    pid = fork();
    if (pid < 0)
	printf("Error in fork()\n");
    else if (pid == 0)
    {
	size = write(fd1[1], "Message from child", 19);
	if(size != 19)
	{
	    printf("Can\'t write all string\n"); 
	    exit(-1); 
	}
	
	size = read(fd2[0], string, 20);                                       
                                                        
        if(size < 0)                                                            
        {                                                                       
            printf("Can\'t read string\n");                                     
            exit(-1);                                                           
        }  
        
        printf("I\'m child, I've received \"%s\"\n", string);
    }
    else 
    {
	size = read(fd1[0], string, 19);

	if(size < 0)
	{
	    printf("Can\'t read string\n"); 
	    exit(-1); 
	} 

	printf("I\'m parent, I've received \"%s\"\n", string);
	
	size = write(fd2[1], "Message from parent", 20);                                      

        if(size != 20)                                                          
        {                                                                       
            printf("Can\'t write all string\n");                                
	    exit(-1);                                                           
        }
    }
    
    if(close(fd1[0]) < 0)
    { 
	printf("Can\'t close input stream\n");
    }

    if(close(fd1[1]) < 0)
    { 
	printf("Can\'t close output stream\n");
    }
    
    if(close(fd2[0]) < 0)
    { 
	printf("Can\'t close input stream\n");
    }

    if(close(fd2[1]) < 0)
    { 
	printf("Can\'t close output stream\n");
    }
    
    return 0;
}