#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FILE_FIFO "./myfifo"
#define BUFF_SIZE 1024 

int main(int argc,char const *argv[])
{
    char buff[BUFF_SIZE];
    int fd;

    mkfifo(FILE_FIFO,0666);

    //Consumer <=> Read first 
    while(1){
        fd=open(FILE_FIFO,O_RDONLY);

        read(fd,buff,BUFF_SIZE);

        printf("Message from producer : %s",buff);

        close(fd);

        printf("Respone to producer: ");fflush(stdin);
        fgets(buff,BUFF_SIZE,stdin);
        printf("\n");
        fd=open(FILE_FIFO,O_WRONLY);

        write(fd,buff,strlen(buff)+1);

        close(fd);
    }

    return 0;
}