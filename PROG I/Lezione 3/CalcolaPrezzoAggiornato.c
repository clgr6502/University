#include <stdio.h>
int main(){
   int sc;
   float pi, pe, pf;
   if(scanf("%d %f %f", &sc, &pi, &pe) != 3
   || pi < 0 || (pe < 0 && pe > 100)
   || (sc != 0 && sc != 1)){
       printf("invalid input\n");
       return 0;
   }
   if(sc == 0){
      pf = pi - (pi * pe / 100);
      printf("%20s\t%20s\t%20s\n", "Prezzo_Init",
            "Percentuale", "Prezzo_scontato");
   }
   else if(sc == 1){
      pf = pi + (pi * pe / 100);
      printf("%20s\t%20s\t%20s\n", "Prezzo_Init",
            "Percentuale", "Prezzo_ivato");
   }
   printf("%20.2f\t%20.2f\t%20.2f\n", pi, pe, pf);
   return 0;
}