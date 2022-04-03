#include <stdio.h>

float leggi_prezzo(float a);
float leggi_percentuale(float b);
void calcola_prezzo_ivato(float a, float b);
void calcola_prezzo_scontato(float a, float b);

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

   prezzoIniziale = leggi_prezzo(prezzoIniziale);

   percentuale = leggi_percentuale(percentuale);

   printf("%20s\t%20s\t", "Prezzo_Init", "Percentuale");

   if(scelta == 0){
      calcola_prezzo_scontato(prezzoIniziale, percentuale);
   }
   else if(scelta == 1){
      calcola_prezzo_ivato(prezzoIniziale, percentuale);
   }
   }
   return 0;
}

float leggi_prezzo(float a){
   while(scanf("%f", &a) != 1 || a <= 0){
      printf("Prezzo non valido\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }  
   return a;
}

float leggi_percentuale(float b){
   while(scanf("%f", &b) != 1 ||
   b < 0 || b > 100){
      printf("Percentuale non valida\n");
      scanf("%*[^\n]");
      scanf("%*c");
   }
   return b;
}

void calcola_prezzo_scontato(float a, float b){
   float c;
   printf("%20s\n", "Prezzo_scontato");
   c = a - (a * b / 100);

   printf("%20.2f\t%20.2f\t%20.2f\n", a,
   b, c);
}

void calcola_prezzo_ivato(float a, float b){
   float c;
   printf("%20s\n", "Prezzo_ivato");
   c = a + (a * b / 100);
   printf("%20.2f\t%20.2f\t%20.2f\n", a,
   b, c);
}
