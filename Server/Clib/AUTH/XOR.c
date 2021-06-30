#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
   char test[100]="45";
   char test2[100]="123";
   printf("b : %s\n",test);
   printf("b : %s\n",test2);
   strcat(test,test2);
// //    strcat(test2,test);
   printf("a : %s\n",test);
//    printf("a : %s\n",test2);
   printf("SIZE = %ld\n",strlen(test));

    return 0;
}