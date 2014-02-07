#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main()
{
    int fd;
    size_t length; 
    int i; 

    int *ptr;

    fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);
    

    if (fd == -1)
    {    
	printf("File open failed!\n");
	exit(1);
    }

    length = 100000*sizeof(int);

    ftruncate(fd,length);

    ptr = (int *)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    close(fd);

    if (ptr == MAP_FAILED)
    {
	printf("Mapping failed!\n");
	exit(2);
    }
    (*ptr)++;
        printf("%d", *ptr);

    munmap((void *)ptr, length);
    return 0;
}
