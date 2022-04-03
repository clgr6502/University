#include <stdio.h>

int mcd(int a, int b);
int mcm(int a, int b);

int main(){
   int n, m;

   while(scanf("%d %d", &n, &m) != 2 || n < 0 || m < 0){
      printf("Inserisci un intero positivo.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   printf("%d\n%d\n", mcd(n, m), mcm(n, m));

   return 0;
}

int mcd(int a, int b){
   int j;

   while(b != 0){
      j = a % b;
      a = b;
      b = j;
   }return a;
}

int mcm(int a, int b){
   return (a*b)/mcd(a, b);
}