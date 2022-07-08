#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define LENMAX 100

int main(int argc, char **argv){
   if(argc == 1){
      printf("Utilizzo: mywc [-l -w] file1 [file2 file3 ….]\n");
      exit(1);
   }
 
   FILE *in;
   int lenmax = 100;

   int wflag       = 0;
   int lflag       = 0;
   int wcounter    = 0;
   int scounter    = 0;
   int ctrlcounter = 0;
   int charcounter = 0;
   int lcounter    = 0;

   char *line = malloc(sizeof(char*) * LENMAX);
   int opt;

   while((opt = getopt(argc, argv, "lw")) != -1){
      switch(opt){
         case 'w':
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

   if(wflag == 0 && lflag == 0){
      in = fopen(argv[1], "r");
   }else{
      in = fopen(argv[2], "r");
   }

   if(in == NULL){
      printf("Errore nell'apertura del file.\n");
      exit(1);
   }
   while(!feof(in)){
      getline(&line, &lenmax, in);
      lcounter++;

      int i = 0;
      while(i < strlen(line)){
         if(isspace(line[i]) && !iscntrl(line[i])){
            scounter++;
            i++;
         }else if(iscntrl(line[i])){
            ctrlcounter++;
            i++;
         }else{
            wcounter++;
            charcounter++;
            i++;
            while(!isspace(line[i]) && !iscntrl(line[i])){
               charcounter++;
               i++;
            }
         }
      }
   }
      
   if(!wflag && !lflag){
      printf("Parole, righe, caratteri, spazi, ctrl\n");
      printf("%d, %d, %d, %d, %d\n", wcounter, lcounter, charcounter, scounter, ctrlcounter);
   }else if(wflag && !lflag){
      printf("Parole\n");
      printf("%d\n", wcounter);
   }else if(!wflag && lflag){
      printf("Righe\n");
      printf("%d\n", lcounter);
   }else{
      printf("Parole, righe\n");
      printf("%d, %d\n", wcounter, lcounter);
   }

   free(line);
   free(in);
   return 0;
}
