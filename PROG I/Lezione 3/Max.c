#include <stdio.h>

int main(){
   int a, b, c;
   scanf("%d %d %d", &a, &b, &c);

   if(a > b){
      if(a > c){
         printf("%d\n", a);
      }
      else{
         printf("%d\n", c);
      }
   }
   else{
      if(c > b){
         printf("%d\n", c);
      }
      else{
         printf("%d\n", b);
      }
   }
   return 0;
}
