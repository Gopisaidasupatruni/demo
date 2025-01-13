/* This program is to replace a person town in a file with another person town which doesnt effect other information */
/* Author : Gopisai
 * Date :30/9/2024
 */ 
/* REQUIRED HEADER FILES */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	FILE*fp;
	fp = fopen("file","w");
	if(fp < 0)
	{
		printf("error\n");
		return 0;
	}
	char ch,i=0,j=0;
	/* To store names */
	char str1[20];
	char str2[20];

	/* Enter data into a file*/
	printf("Enter the data into a file\n");
	while( (ch = getchar()) != EOF ) 
		fputc(ch,fp);

	fclose(fp);


	/* Get the size of the file. */
	long file_size;
	char *file_content;
	fp = fopen("file","r");
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);
	/* creating dynamic memory */
	file_content = (char *)malloc((file_size + 1) * sizeof(char));
	fread(file_content, sizeof(char), file_size, fp);
	file_content[file_size] = '\0'; 
        /* To store string to swap */
	fseek(fp,6,0);
	while((ch=fgetc(fp))!='\n')
	{
		str1[i++]=ch;
	}
	str1[i]='\0';
	//        printf("%ld\n",ftell(fp));
	printf("\n");
	/* Actual string */
	fseek(fp,17,0);
	while((ch=fgetc(fp))!='\n')
	{
		str2[j++]=ch;

	}
	str2[j]='\0';
	fclose(fp);

        /* Again opening file in read and write mode */
	fp = fopen("file","r+");

	int n1=strlen(str1);

	int n2=strlen(str2);
	fseek(fp,12,0);
	if(n2>n1)
	{
		int len=n2-n1;
		char *new_file_content = (char *)malloc((file_size + len+ 1) * sizeof(char));
		if (new_file_content == NULL) {
			printf("Memory allocation error\n");

			return 1;
		}


		strncpy(new_file_content, file_content, 6);


		strcpy(new_file_content + 6, str2);

		strcpy(new_file_content + 6 + n2, file_content + 6 + n1);

		free(file_content);
		file_content = new_file_content;
	}



	fclose(fp);

	fp = fopen("file", "w");



	fputs(file_content, fp);


	free(file_content);
	fclose(fp);	
}
