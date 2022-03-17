#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*Per l'Overflow*/
#include <limits.h>

/*L'espressione sarà di
  lunghezza massima 30 */
#define MAX 30

struct nodo{
   int val;
   struct nodo *next;
};/*Nodo stack*/

void push(struct nodo **lptr, int val);
void stampaInC2(int risultato);
int numero(char *num);
int pop(struct nodo **lptr);
int check(int a, int b, char c, int *ris);
int op(int a, int b, char c);

int main(){
   int cifra, *ris, flag = 0;
   char *espressione = malloc(MAX);
   struct nodo *lptr = NULL;

   scanf("%[^\n]%*c", espressione);
   /*Fino all'inserimento della parola "fine"*/
   while(strcmp(espressione, "fine") != 0){
      char *token = strtok(espressione, " ");

      while(token != NULL && flag == 0){
         /*Se il token è un numero*/
         if(numero(token)){
            /*Nello stack*/
            push(&lptr, atoi(token));
         }
         /*Se non lo è (quindi un operando)*/
          else{
            /*Estraggo 2 numeri*/
            int a = pop(&lptr);
            int b = pop(&lptr);
            char op = token[0];

            flag = check(a, b, op, &ris);

            if(flag){
               /*In caso di overflow*/
               printf("Overflow!\n");
            }
            else{
               push(&lptr, ris);
            }
         }
         /*Scorre l'espressione*/
         token = strtok(NULL, " ");
      }
      if(!flag){
         int risultato = pop(&lptr);

         printf("%d in C2: ", risultato);
         stampaInC2(risultato);
      }
      scanf("%[^\n]%*c", espressione);
      flag = 0;
   }
   /*Libero la memoria*/
   free(espressione);
   return 0;
}
/*Push dello Stack*/
void push(struct nodo **lptr, int val){
   struct nodo *nuovo = malloc(sizeof(struct nodo));

   if(nuovo != NULL){
      nuovo->val = val;
      nuovo->next = *lptr;
      *lptr = nuovo;
   }
}
/*Verifica che sia un numero*/
int numero(char *num){
   if(strlen(num) > 1){
      /*Un operatore è un singolo carattere.
        se è più lungo, è un numero*/
      return 1;
   }
   else{
      if(num[0] < '0' || num[0] > '9'){
         return 0;
      }
   }
   return 1;
}
/*Pop dello stack*/
int pop(struct nodo **lptr){
    struct nodo *temp = *lptr;

    int val = (*lptr)->val;
    *lptr = (*lptr)->next;
    free(temp);

    return val;

}
/*Controllo OF e operazioni*/
int check(int a, int b, char c, int *ris){
   switch(c){
      case '+':
         /*OF se, con gli operandi positivi, uno dei 2
           è maggiore del massimo rappresentabile*/
         if((a > 0 && b > 0 && a > INT_MAX - b)
         || (a < 0 && b < 0 && a < INT_MIN - b)){
            return 1;
         }
         else{
            *ris = a + b;
            return 0;
         }
      break;
      case '-':
         /*Come per la somma, al contrario*/
         if((a > 0 && b < INT_MIN + a)
         || (a < 0 && b > INT_MAX + a)){
            return 1;
         }
         else{
            *ris = b - a;
            return 0;
         }
      break;
      case '*':
         if((b > 0 && a > INT_MAX / b)
         || (b < 0 && a < INT_MIN / b)){
            return 1;
         }
         else{
            *ris = a * b;
            return 0;
         }
      break;
      default:
         printf("operatore non valido!\n");
      break;
   }
}
/*Stampa in complemento a 2*/
void stampaInC2(int risultato){
   const int bit = sizeof(unsigned int) * CHAR_BIT;
   unsigned int j = 1;

   for(int i = 0; i < bit; i++){
      unsigned int maschera = 1u << (bit - 1 - i);
      printf("%c", (risultato & maschera) ? '1' : '0');
      if(j % 4 == 0)
         printf(" ");
         j++;
      }
   printf("\n");
}
