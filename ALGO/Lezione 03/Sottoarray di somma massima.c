#include <stdio.h>

int main(){
   int n;
   scanf("%d", &n);

   int a[n];

   for(int i = 0; i < n; i++){
      scanf("%d", &a[i]);
   }

   int somma = 0;
   int sm = 0;

   for(int i = 0; i < n; i++){
      if(a[i] > 0){
         somma += a[i];
      }
      else{
         if(somma > sm){
            sm = somma;
         }
         somma = 0;
      }
   }

   if(sm != 0){
      printf("%d", sm);
   }
   else{
      printf("%d", somma);
   }

   return 0;
}
    