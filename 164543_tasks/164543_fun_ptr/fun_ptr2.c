/* Using arrays */
/* REQUIRED HEADER FILE */
#include<stdio.h>
/*FUNCTION PROTOTYPES */
int sum(int a,int b);
int sub(int c,int d);
/*MAIN PROGRAM */
/*main: function pointers using arrays */
int main()
{
        int ivar,ivar1,ivar2,iop=1;
	/* array of function pointer */
        int (*fp[2])(int,int) = {&sum,&sub};
        printf("Enter the x,y values\n");
        scanf("%d%d",&ivar,&ivar1);
	/* function call */
	ivar2=fp[iop-1](ivar,ivar1);
	printf("%d\n",ivar2);
	ivar2=fp[iop](ivar,ivar1);
	printf("%d\n",ivar2);
}
/* sum: To sum two numbers */
int sum(int a,int b)
{
	/* adding */
	int inum=a+b;
	return inum;
}
/* End sum */
/* sub: To subtract two numbers */
int sub(int c,int d)
{
	/* subtraction */
	int inum=c-d;
	return inum;
}
/* End sub */

