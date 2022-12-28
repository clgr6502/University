//FILE MODIFICATO PER GIT
//PROVA PROVA
#include <stdio.h>
int main(){
   int x;

   while(scanf("%d", &x) != 1 || x < 0){
      printf("Incorretto. Inserisci un intero positivo.\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }
   for(int a = 1; a <= 10; a++){
      printf("%d\n", x * a);
   }
   return 0;
}
