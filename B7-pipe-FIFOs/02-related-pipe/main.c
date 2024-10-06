#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_SIZE 20
char *msg1 = "Hello World #1!";
char *msg2 = "Hello World #2!";
char *msg3 = "Hello World #3!";

void func(int num){
    wait(NULL);
    printf("Child process terminated!\n");
}

int main(int argc,const char *argv[])
{
    char buff_msg[MAX_SIZE];
    pid_t child_pid;
    int fd[2];
    int numb_read,numb_write;

    if(pipe(fd)<0){
        fprintf(stderr,"Can not create pipe!\n");
        exit(0);
    }

    child_pid=fork();

    if(child_pid>=0){
        if(child_pid==0){
            printf("I'm child process with rule is reader!\n");//reader
            if(close(fd[1])==-1){                              //writer do no use
                printf("close(fd[1]) failed!\n");
            }

            while(1){
                numb_read=read(fd[0],buff_msg,MAX_SIZE);
                if(numb_read<0){
                    printf("Read failed!\n");
                    exit(0);
                }else if(numb_read==0){
                    printf("End of pipe -> Exit!\n");
                    break;
                }else{
                    printf("Message from pipe:%s\n",buff_msg);
                }
            }
        }else{
            signal(SIGCHLD,func);
            printf("I'm parents process with rule is writter!\n");
            if(close(fd[0])==-1){                              //reader do no use
                printf("close(fd[0]) failed!\n");
            }

            write(fd[1],msg1,MAX_SIZE);
            write(fd[1],msg2,MAX_SIZE);
            write(fd[1],msg3,MAX_SIZE);

            // if(close(fd[1])==-1){                              //reader will see end of pipe
            //     printf("close(fd[1]) failed!\n");
            // }

            while(1);
        }
    }else{
        printf("fork() unsucessfully!\n");
    }
}