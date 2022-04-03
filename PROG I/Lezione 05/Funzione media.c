#include <stdio.h>

void media();

int main(){
   media();
   return 0;
}

void media(){
   int primo, n, c = 0;
   float media = 0;

   for(int i = 0; i < 10; i++){
      while(scanf("%d", &n) != 1){
         printf("Inserisci un intero.\n");
         scanf("%*[^\n]");
         scanf("%*c");
      }
      if(i == 0){
         primo = n;
      }
      if((primo > 0 && n > 0) || (primo < 0 && n < 0)){
         media = media + n;
         c++;
      }
      if(i == 9){
         media = media / c;
         printf("%.2f\n", media);
      }
   }
}