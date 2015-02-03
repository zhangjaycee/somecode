/*******************************************
20150203 byJaycee
zhjcyx@gmail.com
这个程序是用递归实现求前N项自然数列和
(在不用if while 乘除的限制下实现)
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
