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

   int o = n + m;
   int c[o];

   int j = 0;
   int k = 0;
   int i = 0;

   while(j < n && k < m){
      if(a[j] < b[k]){
         c[i] = a[j];
         j++;
      }
      else{
         c[i] = b[k];
         k++;
      }
      i++;
   }

   while(j < n){
      c[i] = a[j];
      j++;
      i++;
   }

   while(k < m){
      c[i] = b[k];
      k++;
      i++;
   }

   for(int i = 0; i < o; i++){
      printf("%d\n", c[i]);
   }

   return 0;
}
