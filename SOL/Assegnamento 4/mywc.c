#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define LENMAX 100

int main(int argc, char **argv){
   if(argc == 1){
      printf("Utilizzo: mywc [-l -w] file1 [file2 file3 …]");
      exit(1);
   }
 
   FILE *in = fopen(argv[1], "r");

   int wflag = lflag = 0;
   int wcounter = 0;
   int scounter = 0;
   int ctrlcounter = 0;
   int lcount = 0;

   char *line = malloc(sizeof(char*) * LENMAX);
   int opt;

   while((opt = getopt(argc, argv, "lw:")) != -1){
      switch(opt){
         case 'w'':
            wflag = 1;
         break;

         case 'l':
            lflag = 1;
         break;

         default:
            printf("Argomento sconosciuto.\n");
         break;
      }
   }

   if(in == NULL){
      printf("Errore nell'apertura del file.\n");
      exit(1);
   }

   do{
      fscaf(in, "%^[\n]%*c", line);

      if(lflag){
         lcount++;
      }

      for(int i = 0; i < strlen(line); i++){
         if(isspace(line[i])){
            scounter++;
         }else if(isctrl(line[i])){
            ctrlcounter++;
         }else if(wflag){
               wcounter++;
               i++;
               while(!isspace(line[i])){
                  i++;
               }
            }
         }
      }
   }while(!feof(in));
   
   free(line);
   free(in);

   return 0;
}