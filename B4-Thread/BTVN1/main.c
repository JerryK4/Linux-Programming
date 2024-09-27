#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


pthread_t thread_id1,thread_id2;

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

void *thread_handle(void *args)
{
    thr_data_t *data=(thr_data_t*)args;

    if(pthread_equal(thread_id1,pthread_self())){
        printf("Hello Jerry! I am thread 1\n");
    }else if(pthread_equal(thread_id2,pthread_self())){
        printf("I am thread 2!\n");
        printf("My name: %s , My birthday: %d/%d/%d, My phone number: %s, My home: %s\n",data->name,data->d.day,data->d.month,data->d.year,data->phone,data->home);
    }
}

void destring(char x[]){
    size_t len=strlen(x);
    if(x[len-1]=='\n'){
        x[len-1]='\0';
    }
}

void input(thr_data_t *data)
{
    char n[30];
    printf("\nYour name : ");
    fflush(stdin);fgets(n,sizeof(n)+1,stdin);destring(n);
    strncpy(data->name,n,sizeof(data->name));

    printf("\nYour birthday: ");
    int a,b,c;scanf("%d %d %d",&a,&b,&c);getchar();
    data->d.day=a;data->d.month=b;data->d.year=c;

    char p[10];
    printf("\nYour phone number : ");
    fflush(stdin);fgets(p,sizeof(p)+1,stdin);destring(p);
    strncpy(data->phone,p,sizeof(data->phone));

    char h[30];
    printf("\nYour home : ");
    fflush(stdin);fgets(h,sizeof(h)+1,stdin);destring(h);
    strncpy(data->home,h,sizeof(data->home));
}
int main(int argc,char *argv[])
{
    int ret;

    thr_data_t data;
    memset(&data,0x0,sizeof(data));

    input(&data);
    if(ret=pthread_create(&thread_id1,NULL,&thread_handle,NULL))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }
    sleep(3);
    if(ret=pthread_create(&thread_id2,NULL,&thread_handle,&data))
    {
        printf("pthread_create() error number:%d\n",ret);
        return -1;
    }

    pthread_join(thread_id1,NULL);
    pthread_join(thread_id2,NULL);
    return 0;
}