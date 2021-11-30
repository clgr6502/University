#include <stdio.h>

int main(){
   int x;
   scanf("%d", &x);

   for(int i = 2; i < 10; i++){
      if(x % i == 0){
         printf("0\n");
         break;
      }
      else{
         printf("1\n");
         break;
      }
   }
   return 0;
}
