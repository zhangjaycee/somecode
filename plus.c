/*******************************************
20150203 byJaycee
zhjcyx@gmail.com
����������õݹ�ʵ����ǰN����Ȼ���к�
(�ڲ���if while �˳���������ʵ��)
********************************************/


#include<stdio.h>
int sum=0;
int func(int n)
{
	sum+=n;
//	printf("sum now = %d\n",sum);
	return (!n)||func(--n);
}
int main()
{

	func(3);
	printf("%d\n",sum);
	return 0;
}
