#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

char *my_strcat1(char *s1, char *s2);

int main(){
   char *s1 = malloc(MAX * sizeof(char));
   char *s2 = malloc(MAX * sizeof(char));

   scanf("%s %s", s1, s2);

   printf("%s\n", my_strcat1(s1, s2));

   return 0;
}

char *my_strcat1(char *s1, char *s2){
   int l = strlen(s1);

   for(int j = 0; (s1[j + l] = s2[j]) != '\0'; j++);

   return s1;
}