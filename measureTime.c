#include<stdio.h>
#include<time.h>

int main(void)
{
    int i=0,j=0;
    struct timespec tStart,t1,tEnd;
    long td,td1;

    clock_gettime(CLOCK_MONOTONIC,&tStart);
    
    printf("hello,world!\n");
    
    clock_gettime(CLOCK_MONOTONIC,&t1);

    for(i=0;i<100;i++){
        for(j=0;j<1000;j++){
            
        }
    }

    clock_gettime(CLOCK_MONOTONIC,&tEnd);
    
    td1=t1.tv_nsec-tStart.tv_nsec;
    td=tEnd.tv_nsec-tStart.tv_nsec;

    printf("td1=%ldms,td=%ldms,td1/td=%lf\n",td1/1000,td/1000,(double)td1/td);
    
    return 0;
}
