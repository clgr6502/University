#include <stdio.h>

int read_int(int a);
int multipli(int c, int d);

int main(){
   int n, m;
   n = read_int(n);
   m = read_int(m);

   multipli(n, m);
   return 0;
}

int read_int(int a){
   while(scanf("%d", &a) != 1){
      printf("Inserisci un intero.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }
   return a;
}

int multipli(int c, int d){
   for(int i = 2; i < c; i++){
      if(i % d == 0){
         printf("%d\n", i);
      }
   }
}