#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define LISTEN_BACKLOG 50
#define BUFF_SIZE 256 
#define handle_error(msg)\
    do{perror(msg);exit(EXIT_FAILURE);}while(0) 

void chat_func(int new_socket_fd)
{
    int numb_read,numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while(1){
        memset(sendbuff,'0',BUFF_SIZE);
        memset(recvbuff,'0',BUFF_SIZE);

        /*Đọc dữ liệu từ Socket*/
        /*Hàm read sẽ block cho đến khi đọc được dữ liệu từ socket*/
        numb_read=read(new_socket_fd,recvbuff,BUFF_SIZE);

        if(numb_read<0){
            handle_error("read()");
        }else if(strncmp(recvbuff,"exit",4)==0){
            system("clear");
            break;
        }
        printf("\nMesseage from client: %s\n",recvbuff);

        printf("\nPlease reponse to client: ");fgets(sendbuff,BUFF_SIZE,stdin);
        numb_write=write(new_socket_fd,sendbuff,BUFF_SIZE);
        if(numb_write<0){
            handle_error("read()");
        }else if(strncmp(recvbuff,"exit",4)==0){
            system("clear");
            break;
        }
    }
    sleep(1);
    close(new_socket_fd);
}

int main(int argc,const char *argv[])
{
    int port_no,len,opt;
    int server_fd,client_fd;
    struct sockaddr_in serv_addr,client_addr;

    /*Đọc port number trên command line*/
    if(argc<2){
        printf("No port provided\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }else{
        port_no=atoi(argv[1]);//Chuyển String sang int
    }

    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    memset(&client_addr,0,sizeof(struct sockaddr_in));

    /*Tạo socket*/
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd==-1){
        handle_error("socket()");
    }
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))==-1){
        handle_error("setsockopt()");
    }

    /*Khởi tạo địa chỉ cho server*/
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port_no);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    /*Gắn socket với địa chỉ server*/
    if(bind(server_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        handle_error("bind()");
    }

    /*Nghe tối đa 50 lần trong hàng đợi*/
    if(listen(server_fd,LISTEN_BACKLOG)==-1){
        handle_error("listen()");
    }
    /*Lấy thông tin từ client*/
    len=sizeof(client_addr);

    while(1){
        printf("Server is listening at port:%d \n....\n",port_no);
        client_fd=accept(server_fd,(struct sockaddr*)&client_addr,(socklen_t *)&len);
        if(client_fd==-1)
            handle_error("accept()");
        system("clear");

        printf("Server:got connect\n");
        chat_func(client_fd);
    }
    close(server_fd);
    return 0;
}