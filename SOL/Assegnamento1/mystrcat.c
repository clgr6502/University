//Versione copiata a mano
//possibili typo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Per gli argomenti
#include <stdarg.h>

const int REALLOC_INC = 16;

void RIALLOCA(char **buf, size_t newsize);
char *mystrcat(char *buf. size_t sz, char *first, ...);

int main(int argc, char **argv){
   if(argc < 7){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }
   char *buffer = NULL; 
   RIALLOCA(&buffer, REALLOC_INC);
   
   buffer[0] = '\0';
   buffer = mystrcat(buffer, REALLOC_INC, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], NULL);
  
   printf("%s\n", buffer);
   free(buffer);
  
   return 0;
}

void RIALLOCA(char **buf, size_t newsize){
   *buf = realloc(*buf, newsize);
   if(*buf == NULL){
      printf("Errore memoria terminata\n");
      exit(-1);
   }
}

char *mystrcat(char *buf. size_t sz, char *first, ...){
   va_list va;
   va_start(va, first);
  
   if(sz < strlen(first) + 1){
      RIALLOCA(&buf, sz + strlen(first) + 1);
      sz += strlen(first) + 1;
   }

   char *tmp = malloc(sz);
   strcpy(buf, first);
  
   while((tmp = va_arg(va, char*)) != NULL){
      if(sz < strlen(buf) + strlen(tmp) + 1){
         RIALLOCA(&buf, strlen(buf) + strlen(tmp) + 1);
         sz = strlen(buf) + strlen(tmp) + 1;
      }
      int j = 0;
      for(int i = strlen(buf); i < strlen(buf) + strlen(tmp); i++){
         buf[i] = tmp[j];
         j++;
      }
   }
   va_end(va);
   return buf;
}
