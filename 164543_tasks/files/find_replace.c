/* This program is to replace a person's town in a file with another person's town without affecting other information */

/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* MACRO DEFINITIONS */
#define LEN 100
/* FUNCTION PROTOTYPES */
void findNreplace(char*,char*,char*,int);
/* MAIN PROGRAM */
/* main : To find a string to replace and replaces with replacing string */
int main() {
	FILE *fp;


	char str1[LEN] ;
	char str2[LEN] ;
        /* Opening file in read mode */
	fp = fopen("file1.txt", "r");
	/* if it is not returning */
	if (fp == NULL) {
		printf("Error opening file for reading\n");
		return 1;
	}

	/* Get the size of the file. */
	fseek(fp, 0, SEEK_END);
	/* returns position */
	int file_size = ftell(fp);
	/* points to starting point of file */
	rewind(fp);  

	/* Allocate memory to store the entire file content. */
	char *file_content = (char *)malloc((file_size + 1) * sizeof(char));
	if (file_content == NULL) {
		printf("Memory allocation error\n");
		fclose(fp);
		return 1;
	}

	/* Read the file */
	fread(file_content, sizeof(char), file_size, fp);
	file_content[file_size] = '\0';  
	fclose(fp);

	printf("enter the actual string \n");
	scanf(" %[^\n]",str1);
	printf("enter the replacing string \n");
	scanf(" %[^\n]",str2);
	/* To replace string */
         findNreplace(file_content,str1,str2,file_size);
	/* Write the modified content back to the file. */
	fp = fopen("file1.txt", "w");
	if (fp == NULL) {
		printf("Error opening file for writing\n");
		free(file_content);
		return 1;
	}

	fputs(file_content, fp);

         /* Closing file */
	fclose(fp);

	printf("Data replaced successfully.\n");
        free(file_content);
	return 0;


}
/* End main */

/* findNreplace: To find the string and replace with another string printing remaining data same */
void findNreplace(char *file_content,char *str1,char *str2,int file_size){
	/* Replace str1 with str2 in file_content. */
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char *new_file_content;
		/* Reallocate memory for the new file content. */
		new_file_content = (char *)malloc(file_size + (len1)*10+1);
		if (new_file_content == NULL) {
			printf("Memory allocation error\n");
			return;
			}

	int temp_pos=0;

	char * pos = file_content;
        char *match;
	/* if given string is matcing with content */
	while((match=strstr( pos , str1 ))!=NULL)
	{
		/* printing upto matching string */
		strncpy(new_file_content+temp_pos , pos , match-pos);
		temp_pos +=match-pos;
                /* replacing matching string with given string */
		strcpy(new_file_content+temp_pos,str2);
		temp_pos += len2;
		pos =match+len1;
	
	}
	         /* printing remaining string */
		strcpy(new_file_content+temp_pos,pos);
	
		/* copying obtained string */
	       strcpy(file_content,new_file_content);
	       free(new_file_content);
}
/* End findNreplace */
