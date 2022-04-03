#include <stdio.h>
#include <math.h>

void sum_pow(int n, float x);
int read_positive_int(int n);
float read_positive_float(float x);

int main(){
   int n;
   float x;
   
   n = read_positive_int(n);
   x = read_positive_float(x);
   
   sum_pow(n, x);
   
   return 0;
}

void sum_pow(int n, float x){
   float c = 0;
   for(int i = 0; i <= n; i++){
      c = c + pow(x, i);
   }
   printf("%.2f", c);
}

int read_positive_int(int n){
   while(scanf("%d", &n) != 1 || n < 0){
      printf("Inserisci un intero positivo.\n");
	  scanf("%*[^\n]");
	  scanf("%*c");
   }
   return n;
}

float read_positive_float(float x){
   while(scanf("%f", &x) != 1 || x <= 0){
      printf("Inserisci un numero reale positivo.\n");
	  scanf("%*[^\n]");
	  scanf("%*c");
   }
   return x;
}