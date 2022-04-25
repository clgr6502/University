/*NOTA: 3 files uniti in un unico file sorgente in C per comodità*/

/************tokenizer.h************/
void tokenizer(char *token, char *div);
void tokenizer_r(char *token, char *div);

/**********tokenizer_lib.c***********/
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenizer(char *token, char *div){
   char *tok1 = strtok(token, div);

   while(tok1){
      printf("%s ", tok1);
      tok1 = strtok(NULL, div);
   }
   printf("\n");

   return;
}

void tokenizer_r(char *token, char *div){
   char *buf = NULL;
   char *tok1 = strtok_r(token, div, &buf);

   while(tok1){
      printf("%s ", tok1);
      tok1 = strtok_r(NULL, div, &buf);
   }
   printf("\n");
   return;
}

/*********tokenizer_main.c*********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

int main(int argc, char **argv){
   if(argc != 4){
printf("%d\n", argc);
      printf("Utilizzo: ./nomeprog stringa1 stringa2 1/0\n");
      printf("1/0: rientrante si/no\n");
      exit(1);
   }

   if(argv[3]){
      tokenizer_r(argv[1], ",");
      tokenizer_r(argv[2], ",");
   }else{
      tokenizer(argv[1], ",");
      tokenizer(argv[2], ",");
   }

   return 0;
}
