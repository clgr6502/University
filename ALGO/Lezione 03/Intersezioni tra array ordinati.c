#include <stdio.h>

int main(){
   int n, m;
   scanf("%d", &n);

   int a[n];

   for(int i = 0; i < n; i++){
      scanf("%d", &a[i]);
   }

   scanf("%d", &m);

   int b[m];

   for(int i = 0; i < m; i++){
      scanf("%d", &b[i]);
   }

   int count = 0;
   int i = 0, j = 0;

   while(i < n && j < m){
      if(a[i] == b[j]){
         count++;
         i++;
         j++;
      }
      else if(a[i] < b[j]){
         i++;
      }
      else j++;
   }

   printf("%d\n", count);
   return 0;
}