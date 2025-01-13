#include <setjmp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
   /* Buffer to save the execution context */
   sigjmp_buf env;

   /* Save the current context, returns 0 initially */
   int val = sigsetjmp(env, 1);

   printf("val is %d\n", val);

   /* Prompt user for a new value */
   printf("new val (0 to exit): ");
   scanf("%d", &val);

   /* If val is not 0, jump back to sigsetjmp */
   if (val != 0)
       siglongjmp(env, val);

   /* Program terminates when val == 0 */
   return 0;
}

