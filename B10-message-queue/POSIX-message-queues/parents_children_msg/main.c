#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mqueue.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024 
#define MSG_STOP "exit" 
//Hàm xử lý lỗi
void error_exit(const char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc,const char *argv[])
{
    pid_t pid;
    mqd_t mq; //message queue descriptor
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    //Thiết lập thuộc tính cho message queue
    attr.mq_flags=0;
    attr.mq_maxmsg=10;//Số lượng tin nhắn tối đa trong hàng đợi
    attr.mq_msgsize=MAX_SIZE;//Kích thước tối đa của mỗi tin nhắn
    attr.mq_curmsgs=0;//Số tin nhắn hiện tại trong hàng đợi

    //Tạo tiến trình con
    pid=fork();
    if(pid>=0){
        if(pid>0){
            printf("I'm parent process!\n");
            mq=mq_open(QUEUE_NAME,O_CREAT|O_WRONLY,0644,&attr);
            if(mq==-1){
                error_exit("mq_open() parent");
            }

            //Gửi tin nhắn từ tiến trình cha đến tiến trình con 
            printf("Message to children process: ");fflush(stdin);
            fgets(buffer,MAX_SIZE,stdin);
            if(mq_send(mq,buffer,MAX_SIZE,0)==-1){
                error_exit("mq_send()");
            }

            //Đợi một lúc và gửi tin nhắn kết thúc 
            sleep(1);
            if(mq_send(mq,MSG_STOP,MAX_SIZE,0)==-1){
                error_exit("mq_send() stop");
            }

            //Đợi tiến trình con kết thúc 
            wait(NULL);

            //Đóng và hủy queue 
            mq_close(mq);
            mq_unlink(QUEUE_NAME);
        }else{
            sleep(2);
            printf("I'm children process!\n");
            mq=mq_open(QUEUE_NAME,O_RDONLY);
            if(mq==-1){
                error_exit("mq_open() children");
            }

            //Nhận tin nhắn từ message queue 
            do {
                ssize_t bytes_read;
                bytes_read=mq_receive(mq,buffer,MAX_SIZE,NULL);
                if(bytes_read>=0){
                    buffer[bytes_read] = '\0';//Đảm bảo bufer kết thúc bằng chuỗi NULL
                    printf("Children received: %s\n",buffer);
                }else{
                    error_exit("mq_receive()");
                }
            }while(strncmp(buffer,MSG_STOP,strlen(MSG_STOP))!=0);
        }
    }else{
        printf("fork() unsucessfully!\n");
        error_exit("fork()");
    }
    return 0;
}