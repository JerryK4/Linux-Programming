#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void func(int signum)
{
    printf("I am func!\n");
    wait(NULL);
}
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
            /**When a child is terminated, a corresponding SIGCHLD signal 
             * is delivered to the parent
            */
            signal(SIGCHLD, func);
            printf("I am parent process and my PID:%d\n",getpid());
            while(1);
        }
    }else{
        printf("fork() unsucessfull!\n");
    }
}