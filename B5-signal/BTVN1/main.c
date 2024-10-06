#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>

void signal_hanlde(int num)
{
    printf("Jerry from UET: %d\n",num);
    exit(EXIT_SUCCESS);
}

void signal_hanlde1(int num)
{
    printf("Hello I am signal handle 1: %d\n",num);
    exit(EXIT_SUCCESS);
}

void signal_hanlde2(int num)
{
    printf("Hello I am signal handle 2: %d\n",num);
    exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[])
{
    if(signal(SIGINT,signal_hanlde)==SIG_ERR){
        fprintf(stderr,"Failed handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR1,signal_hanlde1)==SIG_ERR){
        fprintf(stderr,"Failed handle SIGUSR1!\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR2,signal_hanlde2)==SIG_ERR){
        fprintf(stderr,"Failed handle SIGUSR2!\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("Hello world!\n");
        sleep(2);
    }

}