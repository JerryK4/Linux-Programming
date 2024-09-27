#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include <unistd.h>

#define THRESHOLD 10
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
int counter=0;//shared resources

static void *thread_handle1(void *args)
{
   pthread_mutex_lock(&lock);
   while(counter<THRESHOLD)
   {
        counter++;
        printf("counter:%d\n",counter);
        sleep(1);
   }
   pthread_mutex_unlock(&lock);
   pthread_exit(NULL);
}


int main(int argc,char *argv[])
{
    int ret;
    pthread_t thread_id1;
    if(ret=pthread_create(&thread_id1,NULL,&thread_handle1,NULL))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }

    while(1){

        if(counter==THRESHOLD){
            printf("Global variable counter:%d\n",counter);
            break;
        }
    }
    pthread_join(thread_id1,NULL);
    
    return 0;
}