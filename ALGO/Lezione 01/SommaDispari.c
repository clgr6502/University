#include <stdio.h>

int sum(int n);

int main(){
   int a;

   scanf("%d", &a);

   printf("%d\n", sum(a));

   return 0;
}

int sum(int n){
   if(n == 0)
      return 0;
   else if(n == 1)
      return 1;
   else
      return sum(n - 1) + (n * 2 - 1);
}
