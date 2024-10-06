#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
    int n;
    sigset_t new_set;
    sigemptyset(&new_set);

    //sigaddset(&new_set,SIGINT);

    if(sigismember(&new_set,SIGINT)==1){
        printf("SIGINT exits!\n");
    }else{
        printf("SIGINT do not exit!\n");
        sigaddset(&new_set,SIGINT);
        printf("n (0 or 1) = ");scanf("%d",&n);

        switch(n){
            case 0:
                if(sigprocmask(SIG_BLOCK,&new_set,NULL)==0){
                    printf("new_set is blocked!\n");
                }else{
                    perror("sigprocmask");
                }
                break;
            case 1:
                if(sigprocmask(SIG_UNBLOCK,&new_set,NULL)==0){
                    printf("new_set is unblocked!\n");
                }else{
                    perror("sigprocmask");
                }
                break;
            default:
                printf("Invalid!\n");
                break; 
        }
    }

    return 0;
}