#include <stdio.h>

void minmax(int a[], int dim, int *min, int *max);

int main(){
   int a[10];
   int min, max;

   for(int i = 0; i < 10; i++){
      scanf("%d", &a[i]);
   }
   minmax(a, 10, &min, &max);

   return 0;
}

void minmax(int a[], int dim, int *min, int *max){
   *min = a[0];
   *max = a[0];

   int indexm;
   int indexM;

   for(int i = 1; i < dim; i++){
      if(*min > a[i]){
         *min = a[i];
         indexm = i;
      }
      if(*max < a[i]){
         *max = a[i];
         indexM = i;
      }
   }
   printf("%d\n%d\n%d\n%d", indexm, *min, indexM, *max);
}