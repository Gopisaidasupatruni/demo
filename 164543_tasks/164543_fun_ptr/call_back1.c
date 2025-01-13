/* Call back function */
/* Header file */
#include<stdio.h>

/** FUNCTION PROTOTYPES */
int sum(int a,int b);
int sub(int a,int b);
void display(int(*fun)(int,int));

/* MAIN PROGRAM */
/* main: call back function */
int main()
{
	int iNum;
	printf("enter the operation 1 -> sum  2 -> sub \n");
	scanf(" %d",&iNum);
	switch(iNum)
	{
		/* assigning sum */
		case 1:
			display(sum);
			break;
		/* assigning sub */
		case 2:
			display(sub);
			break;
		default:
			printf("invalid option\n");
	}
	
}
/*End main */
/* display : call back function */
void display(int (*fun)(int,int))
{
       /* caaling back */
	int iResult=(*fun)(10,5);
	printf("%d\n",iResult);
}
/* End display */

/* sum: summation of two numbers */
int sum(int a,int b)
{
	int itemp=a+b;
	return itemp;
}
/* subtraction of two numbers */
int sub(int a,int b)
{
	int itemp=a-b;
	return itemp;
}
/* End sub */
