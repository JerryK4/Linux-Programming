#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_MSG 20 

char *msg1 = "Hello World #1!";
char *msg2 = "Hello World #2!";
char *msg3 = "Hello World #3!";
char *msg4 = "Hello World #4!";

char buff_msg[MAX_MSG];
int fd[2],i;
void signal_handle(int num)
{
    printf("I'm signal handle!\n");
    write(fd[1],msg4,MAX_MSG);
}
int main(int argc,char *argv[])
{
    if(signal(SIGINT,signal_handle)==SIG_ERR){
        fprintf(stderr,"Can not handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(fd)<0){
        printf("Can not create pipe!\n");
        exit(0);
    }

    write(fd[1],msg1,MAX_MSG);
    write(fd[1],msg2,MAX_MSG);
    write(fd[1],msg3,MAX_MSG);

    printf("Read from pipe!\n");

    // read(fd[0],buff_msg,MAX_MSG);
    // printf("Message from pipe: %s\n",buff_msg);

    for(i=0;i<3;i++){
        read(fd[0],buff_msg,MAX_MSG);
        printf("msg[%d] : %s\n",i+1,buff_msg);
    }
    return 0;
}

