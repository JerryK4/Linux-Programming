#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_t thread_id ;

void *thread_handle(void *args)
{
    pthread_detach(pthread_self());
}
int main(int argc,char *argv[])
{
    int ret;
    int counter=0;

    while(1)
    {
        if(ret=pthread_create(&thread_id,NULL,&thread_handle,NULL)){
            printf("pthread_create() error number:%d\n",ret);
            break;
        }
        counter++;
        //pthread_join(thread_id,NULL);

        if(counter%1000==0){
            printf("Thread create : %d\n",counter);
        }
    }
    return 0;
}