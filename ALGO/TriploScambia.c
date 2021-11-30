#include <stdio.h>

void tswap(int *x, int *y, int *z);

int main(){

   int a, b, c;

   scanf("%d %d %d", &a, &b, &c);

   tswap(&a, &b, &c);

   printf("%d\n%d\n%d\n", a, b, c);

   return 0;
}

void tswap(int *x, int *y, int *z){
   int tmp, temp;

   tmp = *x;
   *x = *z;
   temp = *y;
   *y = tmp;
   *z = temp;
}
