#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,const char *argv[])
{
    /*code*/
    pid_t child_pid;
    char *data=mmap(0,1,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(data==MAP_FAILED)
    {
        printf("%s: mmap() failed\n",__FILE__);
    }
    *data=65;

    child_pid=fork();

    if(child_pid>=0){
        if(child_pid==0){
            printf("Children started, value = %c\n",++(*data));
            if(munmap(data,sizeof(int)+1)==-1)
            {
                printf("munmap() failed\n");
            }
            exit(EXIT_SUCCESS);
        }else{
            wait(NULL);
            printf("In parent, value = %c\n",*data);
            if(munmap(data,sizeof(int)+1)==-1)
            {
                printf("munmap() failed\n");
            }
            exit(EXIT_SUCCESS);
        }
    }else{
        printf("fork() failed!\n");
    }
    return 0;
}