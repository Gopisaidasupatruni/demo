/* Basic program to understanf how function pointer works
 * Swapping Two numbers
*/
/* Header file */
#include<stdio.h>
/* Function pointer : A pointer which holds function address */
/* Syntax : return_type (*pointer_name)(parameter_types); */
void swap(int*,int*);
/** MAIN PROGRAM */
/* main: swaps two numbers */
int main()
{

	int iNum1=10,iNum2=20;
	/* function pointer */
	void (*fp)(int*,int*);
	/* Assigning address of function */
	fp=&swap;
	/* calling function pointer */
	fp(&iNum1,&iNum2);

	printf("%d %d",iNum1,iNum2);
}
/* End main */
/*swap: To swap two integers */
void swap(int *a ,int *b)
{
	/* Swapping using temporary variable */
	int itemp=*a;
	*a=*b;
	*b=itemp;
}
/* End swap */
