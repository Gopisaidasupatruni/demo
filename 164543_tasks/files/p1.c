/* This program is to replace a person's town in a file with another person's town without affecting other information */
/* Author : Gopisai
 * Date : 30/9/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *fp;

	/* Open the file for writing. */

	char ch;
	char str1[20] ;
	char str2[20] ;


	/* Enter data into the file. */
	/*fp = fopen("file", "w");
	  if (fp == NULL) {
	  printf("Error opening file\n");
	  return 1;
	  }
	  printf("Enter the data into a file (press Ctrl+D to stop):\n");
	  while ((ch = getchar()) != EOF) {
	  fputc(ch, fp);
	  }
	  fclose(fp);
	  getchar();*/
	/* Reopen the file to read the  data. */
	fp = fopen("file", "r");
	if (fp == NULL) {
		printf("Error opening file for reading\n");
		return 1;
	}

	/* Get the size of the file. */
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	rewind(fp);  

	/* Allocate memory to store the entire file content. */
	char *file_content = (char *)malloc((file_size + 1) * sizeof(char));
	if (file_content == NULL) {
		printf("Memory allocation error\n");
		fclose(fp);
		return 1;
	}

	/* Read the entire file into memory. */
	fread(file_content, sizeof(char), file_size, fp);
	file_content[file_size] = '\0';  
	fclose(fp);

	printf("enter the actual string \n");
	scanf(" %[^\n]",str1);
	printf("enter the replacing string \n");
	scanf(" %[^\n]",str2);


	/* Replace str1 with str2 in file_content. */
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char *new_file_content;
	if(len2>len1){
		/* Reallocate memory for the new file content if str2 is longer than str1. */
		new_file_content = (char *)malloc((file_size + (len2 - len1) + 1) * sizeof(char));
		if (new_file_content == NULL) {
			printf("Memory allocation error\n");
			return 1;
		}

	}
	else
		new_file_content=file_content;

	char * pos = file_content;
	int temp_pos=0;

	while((pos=strstr( pos , str1 )))
	{
		strncpy(new_file_content+temp_pos , file_content , pos-file_content);
		temp_pos +=pos - file_content;

		strcpy(new_file_content+temp_pos,str2);
		temp_pos += len2;
		pos += len1;
		strcpy(new_file_content+temp_pos,pos);
		
		pos=file_content+temp_pos;
	}


	/* Write the modified content back to the file. */
	fp = fopen("file", "w");
	if (fp == NULL) {
		printf("Error opening file for writing\n");
		free(file_content);
		return 1;
	}

	fputs(new_file_content, fp);


	fclose(fp);

	printf("Data replaced successfully.\n");

	return 0;
}

