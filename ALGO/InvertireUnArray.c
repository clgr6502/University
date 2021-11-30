#include <stdio.h>
#define N 10000

int main(){
   int n, a;
   int A[N];

   scanf("%d", &n);
   a = n - 1;

   for(int i = 0; i < n; i++){
      scanf("%d", &A[i]);
   }

   int i = 0;

   while(i < a){
      int tmp;
      tmp = A[i];
      A[i] = A[a];
      A[a] = tmp;
      a--;
      i++;
   }

   for(int j = 0; j < n; j++){
      printf("%d\n", A[j]);
   }
   return 0;
}
