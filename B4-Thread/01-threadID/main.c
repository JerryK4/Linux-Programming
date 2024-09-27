#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include <unistd.h>
pthread_t thread_id1,thread_id2;

typedef struct {
    char name[30];
    char msg[30];
}thr_data_t;

// static void *thread_handle(void *args)
// {
//     thr_data_t *data=(thr_data_t *)args;

//     printf("Hello %s, welcome to join %s\n", data->name, data->msg);
// }    =>Segment fault 

static void *thread_handle(void *args)
{
    thr_data_t *data=(thr_data_t *)args;

    if(pthread_equal(thread_id1,pthread_self()))
        printf("I am thread ID1!\n");
    else if(pthread_equal(thread_id2,pthread_self()))
    {
        printf("I am thread ID2!\n");
        printf("Hello %s, welcome to join %s\n", data->name, data->msg);
    }
}
int main(int argc,char *argv[])
{
    int ret;
    thr_data_t data={0};

    strncpy(data.name,"jerry",sizeof(data.name));
    strncpy(data.msg,"UET thread programming",sizeof(data.name));

    if(ret=pthread_create(&thread_id1,NULL,&thread_handle,NULL))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }

    if(ret=pthread_create(&thread_id2,NULL,&thread_handle,&data))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }
    sleep(5);

    return 0;
}