/* function pointer in a function */
/* REQUIRED HEADER FILES */
#include<stdio.h>

/* FUNCTION PROTOTYPES */

int add(int,int);
void execute(int (* fun)(int,int), int,int);
int main()
{
	int iNum1=10,iNum2=20;
	execute(add,iNum1,iNum2);
	
}
void execute(int (*fun)(int,int),int a,int b)
{
	int iResult=add(a,b);
	printf("%d\n",iResult);
}
/* adding two elements */
int add(int a, int b)
{
	int ivar=a+b;

	return ivar;
}
