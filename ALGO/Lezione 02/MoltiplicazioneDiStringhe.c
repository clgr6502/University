#include <stdio.h>
#include <string.h>

#define MAX 100

char *product(char *str, int k);

int main(){
   int n;
   char str[MAX];

   scanf("%s %d", str, &n);

   product(str, n);

   return 0;
}

char *product(char *str, int k){
   for(int i = 0; i < k; i++){
      printf("%s", str);
   }
   printf("\n");
}
