#include <stdio.h>

int fib(int a);

int main(){
   int x;

   while(scanf("%d", &x) != 1 || x < 0){
      printf("Inserire un intero positivo\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   for(int y = 0; fib(y) <= x; ++y){
      printf("%d\n", fib(y));
   }
   return 0;
}

int fib(int a){
   if(a == 0){
      return a;
   }
   else if(a == 1){
      return a;
   }
   else{
      a = fib(a - 1) + fib(a - 2);
      return a;
   }
}