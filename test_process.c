#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>



int num=0;


void process_1()
{	
	int count=0;
	while(num!=5){
		count++;
		printf("[process_1]num not 5,count=%d\n",count);
		if(count>15){
			break;
		}
	}
	
}

void process_2()
{
	int i;
	for(i=0;i<10;i++){
		num++;
	}
	printf("%d ",num);
}

int main()
{
	pid_t child1,child2;
	printf("[main]\t%d\n",num);
	if((child1=fork())==0){//child1
		process_1();
	}else if((child2=fork())==0){//child2
		process_2();
	}
	exit(0);
}
