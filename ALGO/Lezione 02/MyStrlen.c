#include <stdio.h>
#include <string.h>

#define MAX 1000

int my_strlen(char *s);

int main(){
   char a[MAX];

   scanf("%s", a);

   printf("%d\n", my_strlen(a));

   return 0;
}

int my_strlen(char *s){
   int i = 0;
   int len = 0;

   while(s[i] != '\0'){
      len++;
      i++;
   }
   return len;
}

