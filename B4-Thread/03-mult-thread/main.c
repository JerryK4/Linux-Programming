#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include <unistd.h>
pthread_t thread_id1,thread_id2;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
int counter=0;//shared resources

static void *thread_handle1(void *args)
{
   pthread_mutex_lock(&lock);
   printf("I am thread 1,counter: %d\n",counter++);
   pthread_mutex_unlock(&lock);
   pthread_exit(NULL);
}

static void *thread_handle2(void *args)
{
   pthread_mutex_lock(&lock);
   printf("I am thread 2,counter: %d\n",counter++);
   pthread_mutex_unlock(&lock);
   pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    int ret;
    
    if(ret=pthread_create(&thread_id1,NULL,&thread_handle1,NULL))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }
    sleep(5);
    if(ret=pthread_create(&thread_id2,NULL,&thread_handle2,NULL))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }
    return 0;
}