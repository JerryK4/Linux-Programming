#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
    int i;

    printf("Number of arguments: %d\n",argc);

    if(strcmp(argv[1],"-l")==0)
        printf("Hello world!\n");

    if(strcmp(argv[1],"-h")==0)
        printf("Jerry from UET!\n");

    
    for(i=0;i<argc;i++)
    {
        printf("argc[%d]=%s\n",i,argv[i]);
    }

    return 0;
}