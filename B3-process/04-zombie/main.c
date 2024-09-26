#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
    int status;
    pid_t child_pid;

    child_pid=fork();
    if(child_pid>=0)
    {
        if(child_pid==0)
        {
            printf("I am child process and my PID:%d\n",getpid());
            //do nothing
        }else{
            while(1);
            printf("I am parent process and my PID:%d\n",getpid());
            //wait(&status);
        }
    }else{
        printf("fork() unsucessfull!\n");
    }
}