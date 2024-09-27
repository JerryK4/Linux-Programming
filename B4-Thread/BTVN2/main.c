#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

pthread_t thread_id1,thread_id2,thread_id3;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    int day;
    int month;
    int year;
}date;

typedef struct{
    char name[30];
    date d;
    char phone[10];
    char home[30];
}thr_data_t;

thr_data_t *data=NULL;

void destring(char x[]){
    size_t len=strlen(x);
    if(x[len-1]=='\n'){
        x[len-1]='\0';
    }
}

void input(thr_data_t *data)
{   
    memset(data,0,sizeof(thr_data_t));
    char n[30];
    printf("\nYour name : ");
    fflush(stdin);fgets(n,sizeof(n)+1,stdin);destring(n);
    strncpy(data->name,n,sizeof(data->name)-1);

    printf("\nYour birthday: ");
    int a,b,c;scanf("%d %d %d",&a,&b,&c);getchar();
    data->d.day=a;data->d.month=b;data->d.year=c;

    char p[10];
    printf("\nYour phone number : ");
    fflush(stdin);fgets(p,sizeof(p)+1,stdin);destring(p);
    strncpy(data->phone,p,sizeof(data->phone)-1);

    char h[30];
    printf("\nYour home : ");
    fflush(stdin);fgets(h,sizeof(h)+1,stdin);destring(h);
    strncpy(data->home,h,sizeof(data->home)-1);
}
void *thread_handle1(void *args)
{
    thr_data_t *data=(thr_data_t*)args;

    pthread_mutex_lock(&lock);
    printf("I am thread 1!\n");
    input(data);
    pthread_mutex_unlock(&lock);

    return NULL;
}

void File_Input(thr_data_t *data)
{
    int fd=open("./thongtinsinhvien.txt",O_RDWR|O_CREAT|O_APPEND,0666);
    if(fd==-1){
        printf("open() failed!\n");
        return ;
    }
    char result[100];
    snprintf(result,sizeof(result),"%s %d/%d/%d %s %s\n",data->name,data->d.day,data->d.month,data->d.year,data->phone,data->home);
    write(fd,result,strlen(result));
    close(fd);

}
void *thread_handle2(void *args)
{
    thr_data_t *data=(thr_data_t*)args;

    pthread_mutex_lock(&lock);
    printf("I am thread 2!\n");
    File_Input(data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void Read_File(thr_data_t *data) {
    printf("\nMy name is %s\n", data->name);
    printf("\nI was born in %d/%d/%d\n",data->d.day,data->d.month,data->d.year);
    printf("\nMy telephone number is %s\n", data->phone);
    printf("\nI live in %s\n", data->home);
}
void *thread_handle3(void *args)
{
    thr_data_t *data=(thr_data_t*)args;

    pthread_mutex_lock(&lock);
    printf("I am thread 3!\n");
    Read_File(data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc,char *argv[])
{
    while(1){
        int ret;
        data = malloc(sizeof(thr_data_t));
        if (data == NULL) {
            perror("Failed to allocate memory");
            return 1;
        }
        if(ret=pthread_create(&thread_id1,NULL,&thread_handle1,data))
        {
            printf("pthread_create() error number:%d\n",ret);
            return -1;
        }
        pthread_join(thread_id1,NULL);
        if(ret=pthread_create(&thread_id2,NULL,&thread_handle2,data))
        {
            printf("pthread_create() error number:%d\n",ret);
            return -1;
        }
        pthread_join(thread_id2,NULL);
        if(ret=pthread_create(&thread_id3,NULL,&thread_handle3,data))
        {
            printf("pthread_create() error number:%d\n",ret);
            return -1;
        }
        pthread_join(thread_id3,NULL);
        free(data);
    }
    return 0;
}