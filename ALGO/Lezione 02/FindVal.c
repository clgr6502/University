#include <stdio.h>
#define LEN 10

int *FindVal(int a[], int len, int val);

int main(){
   int a[LEN];
   int val;

   for(int i = 0; i < LEN; i++){
      scanf("%d", &a[i]);
   }
   scanf("%d", &val);

   if(FindVal(a, LEN, val) != NULL){
      printf("trovato\n");
   }
   else{
      printf("non trovato\n");
   }
   return 0;
}

int *FindVal(int a[], int len, int val){
   int i;
   for(i = 0; i < LEN; i++){
      if(a[i] != val){
         i++;
      }
      else{
         break;
      }
   }
   if(i >= LEN)
      return NULL;
   else
      return a + i;
}
