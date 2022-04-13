#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
const int REALLOC_INC=16;
 
void RIALLOCA(char** buf, size_t newsize){
   *buf = realloc(*buf, newsize);
}     
char* mystrcat(char *buf, size_t sz, char *first, ...){
   va_list ap;
   va_start(ap, first);

   char *temp = first;

   if(sz < strlen(buf + 1)){
      RIALLOCA(&buf, strlen(buf) + strlen(first) + 1 + REALLOC_INC);
      sz += strlen(first) + 1 + REALLOC_INC;
   }

   while(temp != NULL){
      if(sz < strlen(buf) + 1 + strlen(temp)){
         RIALLOCA(&buf, strlen(temp) + strlen(buf) + 1 + REALLOC_INC);
         sz = strlen(buf) + strlen(temp) + 1 + REALLOC_INC;
      }
      strcpy(buf + strlen(buf), temp);
      temp = va_arg(ap, char *);
   }

   va_end(ap);
   return buf;
}
 
int main(int argc, char *argv[]) {
   if(argc < 7){
      printf("troppi pochi argomenti\n");
      return -1;
   }
   char *buffer = NULL;

   RIALLOCA(&buffer, REALLOC_INC);  // macro che effettua l'allocazione del 'buffer'
   buffer[0]='\0'; // mi assicuro che il buffer contenga una stringa

   buffer = mystrcat(buffer, REALLOC_INC, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], NULL);
   printf("%s\n", buffer);     
   free(buffer);
   return 0;
}
