#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>

void signal_handle(int signum)
{
    printf("Im signal handle1\n");
    exit(EXIT_SUCCESS);
}
int main(int argc,char *argv[])
{
    if(signal(SIGINT,signal_handle)==SIG_ERR){
        fprintf(stderr,"Failed handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    sigset_t new_set;
    sigemptyset(&new_set);
    sigaddset(&new_set,SIGINT);

    if(sigprocmask(SIG_SETMASK,&new_set,NULL)==0){
        if (sigismember(&new_set, SIGINT) == 1 ) {
			printf("SIGINT exist\n");
		} else if (sigismember(&new_set, SIGINT) == 0) {
			printf("SIGINT does not exist\n");
		}
    }

    while(1);

    return 0;
}