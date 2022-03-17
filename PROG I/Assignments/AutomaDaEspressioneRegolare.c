#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 20 /*lunghezza massima stringa*/
#define FUN 12 /*n funzioni*/

void check(char *stringa, int dim);
int automa(int stato, char carattere);

int s0(char caratt); /*lettere o zero*/
int s1(char caratt); /*numero #1*/
int s2(char caratt); /*numero #2*/
int s3(char caratt); /*numero #3*/
int s4(char caratt); /*controllo numeri*/
int s5(char caratt); /*stringa = [A-Z]*011*/
int s6(char caratt); /*numero != da 1*/
int sf0(char caratt);/*Stato finale [A-Z]*0111*/ 
int sf1(char caratt);/*Posso leggere altri 2 numeri*/
int sf2(char caratt);/*Posso leggere un altro numero*/
int sf3(char caratt);/*Non posso più leggere numeri*/
int se(char caratt){}; /*stato errore*/

/*Array di puntatori a funzioni*/
int (*s[FUN])(char) = {s0, s1, s2, s3, s4, s5,
   s6, sf0, sf1, sf2, sf3, se};

int main(){
   char lett;

   int stato = 0;

   while((lett = getchar()) != '\n' && stato != 11){
      stato = (*s[stato])(lett);
      /*scorrimento stato*/
   }
   if(stato > 6 && stato < 11){
      /*Se termina negli stati finali*/
      printf("stringa appartenente al linguaggio\n");
   }
   else{
      printf("stringa non appartenente al linguaggio\n");
   }

   return 0;
}
/*Stati*/
int s0(char caratt){
   if(isupper(caratt)){/*lettera maiuscola*/
      return 0;
   }
   else{
      if(caratt == '0'){
         return 1;
      }
      else{/*numero != 0 || lett. minuscola*/
         return 11;
      }
   }
}

int s1(char caratt){
   if(isdigit(caratt)){/*numero trovato*/
      if(caratt == '1'){
         return 4;
      }
      else{/*altro numero*/
         return 2;
      }
   }
   else{/*trovata lettera*/
      return 11;
   }
}
/*Stringa attuale: [A-Z]*0[02-9]*/
int s2(char caratt){
   if(isdigit(caratt)){/*numero*/
      return 3;
   }
   else{
      return 11;
   }
}
/*Stringa attuale: [A-Z]*0[02-9][0-9]*/
int s3(char caratt){
   if(isdigit(caratt)){/*numero*/
      return 10;
   }
   else{
      return 11;
   }
}
/*Stringa attuale: [A-Z]*01*/
int s4(char caratt){
   if(isdigit(caratt)){
      if(caratt == '1'){
         return 5;
      }
      else{
         return 6;
      }
   }
   else{
      return 11;
   }
}
/*Stringa attuale: [A-Z]*011*/
int s5(char caratt){
   if(isdigit(caratt)){ //ho trovato una cifra
      if(caratt == '1'){
         return 7; //ho letto tre 1 consecutivi
      }
      else{
         return 8;
      }
   }
   else{
      return 11; //lettera
   }
}
/*Stringa attuale: [A-Z]*01[02-9]*/
int s6(char caratt){
   if(isdigit(caratt)){ //ho trovato una cifra
      return 9;
   }
   else{
      return 11;
   }  
}
/*Stati finali*/
int sf0(char caratt){
   if(isdigit(caratt)){
      if(caratt == '1'){
         return 7;
      }
      else{
         return 8;
      }
   }
   else{
      return 11;
   }
}
/*Posso leggere ancora 2 cifre*/
int sf1(char caratt){
   if(isdigit(caratt)){
      return 9;
   }
   else{
      return 11;
   }
}
/*Posso leggere ancora 1 cifra*/
int sf2(char caratt){
   if(isdigit(caratt)){
      return 10;
   }
   else{
      return 11;
   }
}

int sf3(char caratt){
   return 11;
}
