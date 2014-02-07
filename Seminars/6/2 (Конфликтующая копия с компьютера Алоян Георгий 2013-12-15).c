#include <pthread.h>
#include <stdio.h>

int a = 0; 

void *mythread(void *dummy)
{
    pthread_t mythid = pthread_self();
    a++;
    printf("Thread %d, Calculation result = %d\n", mythid, a);
    return NULL;
}

int main()
{
    pthread_t thid1, thid2, mythid;
    int result1 = pthread_create(&thid1, (pthread_attr_t *)NULL, mythread, NULL);
    int result2 = pthread_create(&thid2, (pthread_attr_t *)NULL, mythread, NULL);
    if(result1 != 0)
    {
		printf ("Error on thread create, return value = %d\n", result1);
		exit(-1);
    }
    if(result2 != 0)                                                            
    {                                                                           
        printf ("Error on thread create, return value = %d\n", result2);         
        exit(-1);                                                               
    } 

    printf("Thread 1 created, thid1 = %d\n", thid1);
    printf("Thread 2 created, thid1 = %d\n", thid2); 

    mythid = pthread_self();
    a++;

    printf("Thread %d, Calculation result = %d\n", mythid, a);

    pthread_join(thid1, (void **)NULL);
    pthread_join(thid2, (void **)NULL);

    return 0;
}