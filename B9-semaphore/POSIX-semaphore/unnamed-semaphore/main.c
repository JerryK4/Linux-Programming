#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define NUMS_THREADS 2 //Số lượng thread 

sem_t semaphore ; //khai báo semaphore vô danh 

void* thread_function(void* args){
    int thread_data=*(int*)args;

    printf("Thread %d đang chờ semaphore...\n",thread_data);

    // Chờ semaphore, nếu giá trị semaphore > 0 thì giảm nó đi và tiếp tục, nếu = 0 thì chờ
    sem_wait(&semaphore);

    // Đoạn code này chỉ được thực thi khi đã chiếm được semaphore
    printf("Thread %d đang thực thi...\n", thread_data);
    sleep(2); // Giả lập quá trình làm việc của thread
    printf("Hello I am thread %d <:> \n",thread_data);
    printf("Thread %d hoàn thành.\n", thread_data);

    // Tăng giá trị semaphore để các thread khác có thể tiếp tục
    sem_post(&semaphore);

    return NULL;
}

int main(int argc,const char *argv[])
{
    pthread_t threads[NUMS_THREADS];//Mảng lưu các thread
    int thread_ids_data[NUMS_THREADS]={1,2};//ID cho các thread 

    //Khởi tạo semaphore, giá trị ban đầu = 1,semaphore này không chia sẻ giữa các tiến trình khác nhau
    sem_init(&semaphore,0,1);

    //Tạo các thread 
    for (int i=0;i<NUMS_THREADS;i++){
        pthread_create(&threads[i],NULL,thread_function,&thread_ids_data[i]);
        //sleep(10);
    }

    //Chờ các thread kết thúc 
    for (int i=0;i<NUMS_THREADS;i++){
        pthread_join(threads[i],NULL);
    }

    //Hủy semaphore sau khi hoàn thành 
    sem_destroy(&semaphore);

    return 0;
}