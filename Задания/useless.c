#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

struct Prog
{
    int nTime;
    char* szProgName;
};
time_t stTime = time(&stTime);

int nNumOfStr=0;
struct Prog **arr;
int nCount=0;
size_t sizeStruct;


int ReadFile( datafile )
{   FILE *pf
    int i;
    int ret = 0;
    char* buff;
    pf=fopen(datafile, "r");
    if(pf == -1){
        perror("fopen");
        ret = -1;
        goto err1;
    }
    buffer=(char*)calloc(512, 1);
    while(fscanf(pf, "%m[^\n]", &buff) != EOF)
    {
	nNumOfStr++;
    }
    fseek(pf, 0, SEEK_SET);
    sizeStruct = sizeof(struct Prog);
	arr=(struct Prog**)calloc(nNumOfStr,sizeof(struct Prog*));
	for(i=0; i<nNumOfStr; i++ )
	{

	 arr[i]=(struct Prog *)calloc(1,sizeof(struct Prog));
	 fscanf(pf, "%d %m[^\n]", &(arr[i]->nTime), &(arr[i]->szProgName) );
	 printf("%d %s\n",arr[i]->nTime,arr[i]->szProgName);
	}
	err1:
	    close(pf);
	    return ret;


int Run()
{
    int ret = 0;
	int i;
	int nTime2=0;
	int chpid[nNumeOfStr];

	for(i=0; i<nNumOfStr; i++)
	{
		chpid[i] = fork();
		if(chpid < 0)
		{
			perror("fork");
			ret = -1
			goto err2:
		}
		else if(chpid[i] ==0 )
		{
		    time_t curTime = time(&curTime);
		    arr[i]->nTime = nTime + stTime - curTime;
			sleep(arr[i]->nTime );
			system(arr[i]->szProgName);
		}
		else
		{
			continue;
		}
	}
	for(i=0;i<nNumOfStr; i++)
	{
        wait(NULL);
	}
	err2:

        free(arr);
//        sleep(nTime2);
        return ret;
}


int main(int argc, char** argv)
{
    if(argc != 2){
        printf("Error!Please input name of file\nUsage:./useless <comand file>\n");
        return -1;
    }
    int ret = 0;
	ret = ReadFile(argv[1]);
    if(ret == -1){
        return ret;
    }
	ret = Run();
	return ret;
}










