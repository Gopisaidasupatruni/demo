/*
 * This program is to find determinant value of two dimensional matrix of any given size(n*n)
 */

/* 
 * Author: Gopisai
 * Created Date: 8/10/2024
 */

/* REQUIRED HEADER FILES */
#include<stdio.h>
#include<stdlib.h>

/** FUNCTION PROTOTYPES */
int findDeterminant(int**,int);
/*MAIN PROGRAM */
/* main: To find determinant value of matrix */
int main()
{
	int iNum1,iNum2,irow,icol;

	printf("Enter the number of rows & cols\n");
	scanf("%d%d",&irow,&icol);

	/* Allocating memory dynamically using calloc */
	int **p = (int **)calloc(irow ,sizeof(int *)); 
	for(iNum1=0;iNum1<irow;iNum1++)
		p[iNum1] = (int *)calloc(icol ,sizeof(int));

	/* Scanning array elements */
	printf("Enter the elements into  array\n");
	for(iNum1=0;iNum1<irow;iNum1++) {
		for(iNum2=0;iNum2<icol;iNum2++)
			scanf("%d",&p[iNum1][iNum2]);
	}

	/* Printing array elements */
	printf("displaying the contents\n");
	for(iNum1=0;iNum1<irow;iNum1++) {
		for(iNum2=0;iNum2<icol;iNum2++)
			printf("%d  ",p[iNum1][iNum2]);
		printf("\n");
	}       


	int determinant = findDeterminant(p,irow);

	printf("The determinant of the matrix is: %d\n", determinant);
	/*To free dynamically allocated memory */
	for(iNum1=0 ; iNum1 <irow ; iNum1++)
		free(p[iNum1]);   
	free(p);
	return 0;

}
/* End main */
/* findDeterminant: To find the determinant of a matrix */
int findDeterminant(int**p,int n)
{
	int determinant=0;
	if(n==1)
		return p[0][0];

	/* Calculating determinant of a two dimensional matrix */
	if(n==2){
		determinant = ( p[0][0] * p[1][1] ) - ( p[0][1] * p[1][0] );
		return determinant;

	}
	int **subMatrix = (int **)calloc(n - 1, sizeof(int *));
	for (int i = 0; i < n - 1; i++) {
		subMatrix[i] = (int *)calloc(n - 1, sizeof(int));
	}

	/* Recursive case for larger matrices */
	for (int x = 0; x < n; x++) {
		int sub_i = 0;
		for (int i = 1; i < n; i++) {
			int sub_j = 0;
			for (int j = 0; j < n; j++) {
				if (j == x) {
					continue;
				}
				subMatrix[sub_i][sub_j] = p[i][j];
				sub_j++;
			}
			sub_i++;
		}
		determinant += (x % 2 == 0 ? 1 : -1) * p[0][x] * findDeterminant(subMatrix, n - 1);
	}

	for (int i = 0; i < n - 1; i++) {
		free(subMatrix[i]);
	}
	free(subMatrix);
        /* returning obtained deterinant */
	return determinant;
}
/* End findDeterminant */
