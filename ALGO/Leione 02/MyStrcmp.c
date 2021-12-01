#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int my_strcmp(char *s1, char *s2);

int main(){
   char s1[MAX];
   char s2[MAX];

   scanf("%s %s", s1, s2);

   int c = my_strcmp(s1, s2);

   if(c > 0){
      printf("+");
   }
   printf("%d\n", c);

   return 0;
}

int my_strcmp(char *s1, char *s2){
   int a = strlen(s1);
   int b = strlen(s2);

   int i = 0;

   while(i < a && i < b){
      if(s1[i] == s2[i]){
         i++;
      }
      else if(s1[i] > s2[i]){
         return +1;
      }
      else{
         return -1;
      }
   }
   if(a == b && i == a){
      return 0;
   }
}