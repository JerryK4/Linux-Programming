#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

#define SHARED_MEM_SIZE 100     /*The size (in bytes) of shared memory object*/
#define FILE_NAME "jerry_mmap"  /*Name of the shared memory object*/
#define BUFF_SIZE 1024
/**
 * 1. Tạo fd
 * 2. Set size
 * 3. map/unmap process memory
 * 4. Xóa shared memory segment
 */

int main(int argc,const char *argv[])
{
    /*1.0*/
    int fd=shm_open(FILE_NAME,O_CREAT|O_RDWR,0666);
    if(fd<0){
        printf("shm_open() is failed, %s.\n",strerror(errno));
        return -1;
    }
    /*2.0*/
    ftruncate(fd,SHARED_MEM_SIZE);

    /*3.1*/
    char *data=(char *)mmap(0,SHARED_MEM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    printf("Please writting message: ");fflush(stdin);
    fgets(data,BUFF_SIZE,stdin);
    printf("%s: Write data: %s\n",__FILE__,data);

    /*3.2*/
    munmap(data,SHARED_MEM_SIZE);

    /*4.0*/
    close(fd);
    //shm_unlink(FILE_NAME);

    return 0;
}