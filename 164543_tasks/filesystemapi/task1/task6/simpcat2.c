#include<stdio.h>     
                       
main()                     
{                               
    char c;              
         int i;               
              
    i = read(0, &c, 1);
    while(i > 0) {    
     write(1, &c, 1);
     i = read(0, &c, 1);
  }                                      
}                

