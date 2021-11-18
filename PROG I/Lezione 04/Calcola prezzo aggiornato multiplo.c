#include <stdio.h>

int main(){
   int scelta = 0;
   float prezzoAggiornato, prezzoIniziale, percentuale;
   
   while(scelta >= 0){
   while(scanf("%d", &scelta) != 1 || scelta > 1){
      printf("scelta non valida\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }
   if(scelta < 0)
      return 0;

   while(scanf("%f", &prezzoIniziale) != 1 || prezzoIniziale <= 0){
      printf("Prezzo non valido\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   while(scanf("%f", &percentuale) != 1 ||
    percentuale < 0 || percentuale > 100){
      printf("Percentuale non valida\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }

   printf("%20s\t%20s\t", "Prezzo_Init", "Percentuale");

   if(scelta == 0){
      printf("%20s\n", "Prezzo_scontato");
      prezzoAggiornato = prezzoIniziale - (prezzoIniziale * percentuale / 100);
      printf("%20.2f\t%20.2f\t%20.2f\n", prezzoIniziale,
	 percentuale, prezzoAggiornato);
   }
   else if(scelta == 1){
      printf("%20s\n", "Prezzo_ivato");
      prezzoAggiornato = prezzoIniziale + (prezzoIniziale * percentuale / 100);
      printf("%20.2f\t%20.2f\t%20.2f\n", prezzoIniziale,
	 percentuale, prezzoAggiornato);
   }
   }
   return 0;
}