#include <stdio.h>

int main(){
   int i;
   while(scanf("%d", &i) != 1 || i <= 0){
      printf("Incorretto. Inserisci un intero positivo.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   for(int a = i; a > 0; a-=2){
      for(int j = 0; j < i; j++){
         printf("*");
      }
      printf("\n");
      i -= 2;
   }
   return 0;
}
