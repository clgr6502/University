#include <stdio.h>
#include <string.h>

#define MAX 256

int anagramma(unsigned char *s1, unsigned char *s2);

int main(){
   unsigned char stringa1[MAX];
   unsigned char stringa2[MAX];

   scanf("%s", stringa1);
   scanf("%s", stringa2);

   printf("%d\n", anagramma(stringa1, stringa2));

   return 0;
}

int anagramma(unsigned char *s1, unsigned char *s2){
   int a = strlen(s1);
   int b = strlen(s2);

   if(a != b){
      return 0;
   }
   else{
      int c[26];

      for(int i = 0; i < 26; i++){
         c[i] = 0;
      }

      for(int i = 0; i < a; i++){
         c[s1[i] - 97]++;
         c[s2[i] - 97]++;
      }

      for(int i = 0; i < 26; i++){
         if(c[i] % 2 != 0){
            return 0;
         }
      }
      return 1;
   }
}
