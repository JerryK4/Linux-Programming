#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
    int fd=open("hello.txt",O_CREAT|O_RDWR|O_APPEND,0667);
    ssize_t numb_write,numb_read;
    char buff1[28]="Hello world.Welcome to UET!";
    char buff2[17]="My name is Jerry!";
    char read_buff[45]={0};
    if(fd==-1)
    {
        printf("open() failed!\n");
        return -1;
    }
    numb_write=write(fd,buff1,sizeof(buff1));
    if(numb_write==-1)
    {
        printf("write() failed!\n");
        close(fd);
        return -1;
    }
    printf("Write %ld bytes to file hello.txt\n",numb_write);


    //lseek() con trỏ về đầu file.
    if(lseek(fd,SEEK_SET,0)==-1)
    {
        printf("lseek() failed!\n");
        close(fd);
        return -1;
    }
    numb_write=write(fd,buff2,sizeof(buff2));
    if(numb_write==-1)
    {
        printf("write() failed!\n");
        close(fd);
        return -1;
    }
    printf("Write %ld bytes to file hello.txt\n",numb_write);

    //lseek() con trỏ về đầu file để đọc.
    if(lseek(fd,SEEK_SET,0)==-1)
    {
        printf("lseek() failed!\n");
        close(fd);
        return -1;
    }
    numb_read=read(fd,read_buff,sizeof(read_buff)-1);
    if(numb_read==-1)
    {
        printf("read() failed!\n");
        close(fd);
        return -1;
    }
    printf("String: %s\n",read_buff);
    close(fd);
    return 0;
}