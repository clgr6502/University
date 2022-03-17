/*Unico assignment a non aver preso il punto intero (0.8/1)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Lunghezza max stringa*/
#define MAX 150
#define LIM 15

/*Struttura nodo*/
struct nodo{
   char lettera;
   char *morse;
   struct nodo *next;
};

void inserisci(struct nodo **lptr, char *stringa);
void traduzione(struct nodo *lptr, char strng);
int controllo(char *strng);

int main(){
   FILE *input = fopen("input.txt", "r");
   struct nodo *lptr = NULL;
   int len;
   char *stringa = malloc(LIM);

   if(input == NULL){
      printf("Impossibile aprire file\n");
      exit(1);
   }

   /*Lettura e memorizzazione lettera:morse*/
   while(strcmp(stringa, "****") != 0){
       fscanf(input, "%[^\n]%*c", stringa);
       if(strcmp(stringa, "****") != 0){
          inserisci(&lptr, stringa);
       }
   }
   /*Rialloco la stringa per le frasi*/
   stringa = realloc(stringa, MAX);

   while(fscanf(input, "%[^\n]%*c", stringa) == 1){
      if(controllo(stringa)){
         /*Se la stringa è legittima*/
         for(int i = 0; i < strlen(stringa); i++){
            if(stringa[i] == ' '){
/*Essendo lo spazio un carattere, deve essere seguito da 3 spazi.
  Le frasi sono concatenate da 7 spazi, quindi i 3 dello spazio,
  più 4*/
               printf("%*c", 4, ' ');
            }
            else{
               traduzione(lptr, stringa[i]);
               if(i < strlen(stringa) - 1){
                  /*Spaziatura tra lettere*/
                  printf("%*c", 3, ' ');
               }
            }
         }
         printf("\n");
      }
      else{
         printf("Errore nell'input\n");
      }
   }

   free(stringa);
   fclose(input);

   return 0;
}
/*Inserimento in coda lista*/
void inserisci(struct nodo **lptr, char *stringa){
   /*Divisione in token*/
   char *token = strtok(stringa, ":");
   char lettera = token[0];
   char *morse = malloc(LIM);

   token = strtok(NULL, "\n");
   strcpy(morse, token);

	struct nodo *prec = NULL;
	struct nodo *corr = *lptr;
	struct nodo *tmp = malloc(sizeof(struct nodo));

	while(corr != NULL){
		prec = corr;
		corr = corr->next;
      /*Scorrimento*/
	}
	if(tmp != NULL){
      tmp->morse = malloc(LIM);
		tmp->lettera = lettera;
		strcpy(tmp->morse, morse);
		tmp->next = NULL;
      /*Inserimento valori nel nodo*/
	}
	if(prec == NULL){
		tmp->next = *lptr;
		*lptr = tmp;
      /*Primo inserimento*/
	}
	else{
		prec->next = tmp;
		tmp->next = corr;
	}
}
/*Se la frase è legittima, viene tradotta*/
void traduzione(struct nodo *lptr, char strng){
   struct nodo *prec = lptr;
   struct nodo *corr = lptr->next;

   if(lptr != NULL){
      if(strng == lptr->lettera){
         printf("%s", lptr->morse);
      }
      else{
         while(corr != NULL && corr->lettera != strng){
            prec = corr;
            corr = corr->next;
            /*Se le lettere non coincidono, scorre la lista*/
         }
         if(corr != NULL){
            struct nodo *tmp = corr;
            prec->next = corr;
            printf("%s", corr->morse);
         }
      }
   }
}

int controllo(char *strng){
   for(int i = 0; i < strlen(strng); i++){
      /*In caso di carattere alfanumerico*/
      if(isalnum(strng[i]) || strng[i] == ' '){
         if(isupper(strng[i])){
            /*Se è maiuscolo, lo converte*/
            strng[i] = tolower(strng[i]);
         }
      }
      else{
         return 0;
      }
   }
   return 1;
}
