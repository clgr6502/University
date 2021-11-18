#include <stdio.h>

int fat(int a);

int main(){
   int x, y;
   while(scanf("%d", &x) != 1 || x < 0){
      printf("Incorretto. Inserisci un intero positivo.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }
   y = fat(x);
   printf("%d\n", y);

   return 0;
}

int fat(int a){
   if(a == 0){
      return 1;
   }
   else{
      a = a * fat(a - 1);
   }
   return a;
}