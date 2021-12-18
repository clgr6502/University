#include <stdio.h>
#include <stdlib.h>

void reset(int a[], int len);
void add(int a[], int len, int val);

int main(){
   int a[10];
   int val;

   reset(a, 10);

   scanf("%d", &val);

   while(val >= 0){
      add(a, 10, val);
      scanf("%d", &val);
   };
   
   for(int i = 0; i < 10; i++){
      printf("%d\n", a[i]);
   }

   return 0;
}

void reset(int a[], int len){
   for(int i = 0; i < len; i++){
      a[i] = 0;
   }
}

void add(int a[], int len, int val){
   if(val >= 0 && val < 10){
      a[val] = a[val] + 1;
   }
}
