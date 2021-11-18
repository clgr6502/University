#include <stdio.h>
int main(){
   float a, b, c;
   char operatore;

   scanf("%f %f %c", &a, &b, &operatore);
   scanf("%*[^\n]");
   scanf("%*c");

   if(operatore != '+' && operatore != '-'
   && operatore != '/' && operatore != '%'){
      printf("invalid operator");
   }
   else{
      switch(operatore){
      case '+': c = a + b; break;
      case '-': c = a - b; break;
      case '/': c = a / b; break;
      default:{
            c = (int)a % (int) b;
            break;
         }
      }
   printf("%.1f\n", c);
   }
   return 0;
}