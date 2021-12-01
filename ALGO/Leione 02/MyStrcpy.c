#include <stdio.h>
#include <string.h>

#define MAX 1000

char *my_strcpy(char *dst, char *src);

int main(){
   char s1[MAX];
   char s2[MAX];

   scanf("%s", s1);

   my_strcpy(s2, s1);

   printf("%s\n", s2);

   return 0;
}

char *my_strcpy(char *dst, char *src){
   int a = strlen(src);

   for(int i = 0; i < a; i++){
      dst[i] = src[i];
   }
   dst[a] = '\0';
}