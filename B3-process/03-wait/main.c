#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
int main(int argc,char *argv[])
{
    pid_t child_pid;
    pid_t ret;
    int status;
    child_pid=fork();
    if(child_pid>=0)
    {
        if(child_pid==0)
        {
            printf("I am child process\n");
            printf("My PID: %d, my parent PID: %d\n",getpid(),getppid());
            while(1);
            // printf("Child process is terminated after 5 seconds!\n");
            // sleep(5);
            // exit(0);
        }else{
            ret=wait(&status);
            printf("I am parent process\n");
            printf("My PID: %d and My child process PID:%d\n",getpid(),ret);
            //while(1);
            if(WIFEXITED(status))
            {
                printf("Normally termination, status = %d\n", WEXITSTATUS(status));
            }else if(WIFSIGNALED(status)){
                printf("Killed by signal, value = %d\n", WTERMSIG(status));
            }
        }
    }else{
        printf("fork() unsucessfull!\n");
    }
    return 0;
}