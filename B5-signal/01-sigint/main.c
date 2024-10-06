#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>


void signal_handle1(int num)
{
    printf("I am signal handle 1:%d\n",num);
    //while(1);
    //exit(EXIT_SUCCESS);
}

void signal_handle2(int num)
{
    printf("I am signal handle 2:%d\n",num);
}

void signal_handle3(int num)
{
    printf("I am signal handle 3:%d\n",num);
}
int main(int argc,char *argv[])
{
    if(signal(SIGINT,signal_handle1)==SIG_ERR){
        fprintf(stderr,"Can not handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    // signal(SIGKILL,signal_handle2);
    // signal(SIGTERM,signal_handle3);
    sleep(3);
    kill(getpid(), SIGINT);
    while(1){
        //do nothing
        printf("Hello\n");
        sleep(2);
    }
    return 0;
}