#include<stdio.h>     
                                       
int main() {
	  char c;              
         int i;               
                               
  i = fread(&c, 1, 1, stdin);  while(i > 0) {    
        fwrite(&c, 1, 1, stdout);
        i = fread(&c, 1, 1, stdin);
  }                     
}   

