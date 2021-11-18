#include <stdio.h>

int main(){
   int n, somma = 0, x, i;
   float media;
   while(scanf("%d", &n) < 1 || n < 0){
      printf("Incorretto. Inserisci un intero positivo.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   for(i = 0; i < n; ++i){
      while(scanf("%d", &x) < 1){
        printf("Incorretto. Inserisci un intero.\n");
        scanf("%*[^\n]");
        scanf("%*c");
      }
      somma += x;
   }
   media = (float) somma / n;
   printf("%.2f\n", media);

   return 0;
}