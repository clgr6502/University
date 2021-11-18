#include <stdio.h>
#include <ctype.h>

int main(){
   char a;
   scanf("%c", &a);
   a < 97 ? printf("invalid input") : printf("%c", toupper(a));
   return 0;
}