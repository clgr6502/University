#include <stdio.h>

float calcolopi(int num);

int main(){
   int num;

   while(scanf("%d", &num) != 1 || num <= 0){
      printf("Inserisci un intero positivo.\n");
      scanf("%*c %*[^\n]");
   }

   printf("%f\n", calcolopi(num));
   //printf("%f\n", 4/1-4/3+4/5-4/7+4/9);
   return 0;
}

float calcolopi(int num){
   float a;

   for(int i = 1; i <= num; i++){
      if(i == 1){
         a = 4;
      }
      else if(i % 2 != 0){
         a = a + 4.0f/(i*2.0f-1.0f);
      }
      else{
         a = a - 4.0f/(i*2.0f-1.0f);
      }
   }
   return a;
}