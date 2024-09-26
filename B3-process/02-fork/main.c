#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
    pid_t child_pid;
    int counter=2;

    printf("Gia tri khoi tao cua counter: %d\n",counter);

    child_pid=fork();
    if(child_pid>=0)
    {
        if(child_pid==0)
        {
            printf("I am child process with counter: %d\n",++counter);
            printf("My PID: %d, my parent PID: %d\n",getpid(),getppid());
            //while(1);
        }else{
            printf("I am parent process with counter: %d\n",++counter);
            printf("My PID: %d\n",getpid());
            while(1);
        }
    }else{
        printf("fork() unsucessfull!\n");
    }
    return 0;
}