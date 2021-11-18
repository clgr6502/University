#include <stdio.h>
int main(){
   int h, l;

   while(scanf("%d", &h) != 1 || h < 0){ 
      printf("h incorretto. Introdurre un intero maggiore di 0.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }
   while(scanf("%d", &l) != 1 || l < 0){
      printf("l incorretto. Introdurre un intero maggiore di 0.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   for(int a = 1; a <= h; a++){
      for(int i = 1; i <= l; i++){
         if(i == 1 || i == l
         || a == 1 || a == h){
            printf("*");
         }
         else{
            printf(" ");
         }
      }
      printf("\n");
   }
   return 0;
}