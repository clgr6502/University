#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

char *my_strcat1(char *s1, char *s2);

int main(){
   int a, b;

   scanf("%d", &a);
   char s1[a];
   scanf("%s", s1);

   scanf("%d", &b);
   char s2[b];
   scanf("%s", s2);

   printf("%s\n", my_strcat1(s1, s2));

   return 0;
}

char *my_strcat1(char *s1, char *s2){
   int a = strlen(s1) + strlen(s2) + 1;

   char *b = malloc(a*sizeof(char));

   int i = 0;

   for(int j = 0; j < strlen(s1); j++){
      b[i] = s1[j];
      i++;
   }

   for(int k = 0; k < strlen(s2); k++){
      b[i] = s2[k];
      i++;
   }
   b[a-1] = '\0';

   return b;
}