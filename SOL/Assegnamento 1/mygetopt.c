#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mygetopt(int argc, char **argv);
long isNumber(const char *s);

int main(){
   if(argc < 2){
      printf("Uso: nome-programma -n <numero> -s <stringa> -m >numero> -h\n");
      exit(1);
   }
  
   mygetopt(argc, argv);
  
   return 0;
}

int mygetopt(int argc, char **argv){
   int i = 1;
   int j;
      
   while(i < argc){
      j = 0;
      if(argv[i][j] == '-'){
         while(argv[i][j] == '-'){
            j++;
         }
         long num = 0;

         switch(argv[i][j]){
            case 'n':
            case 'm':
               if(j == strlen(argv[i]) - 1){
                  //passa al prossimo argomento
                  i++;
                  num = isNumber(argv[i]);

                  if(argv[i][0] != '-'){
                     if(num == -1){
                        printf("Argomento non valido ");
                     }else{
                        printf("%ld ", num);
                     }
                  }else{
                     printf("Errore: numero mancante ");
                     continue;
                  }
               }else{
                  j++;
                  num = isNumber(&argv[i][j]);
                  if(num == -1){
                     printf("Argomento non valido ");
                  }else{
                     printf("%ld ", num);
                  }
               }
            break;
            case 's':
               if(j == strlen(argv[i]) - 1){
                  i++;
                  printf("%s ", argv[i]);
               }else{
                  printf("%s ", argv[i] + j + 1);
               }
            break;
            case 'h':
               printf("\nUso: nome-programma -n <numero> -s <stringa> -m >numero> -h.\n");
            break;
            default:
               printf("\nComando sconosciuto ");
               exit(1);
            break;
         }
      i++;
      }else{
         break;
      }
   }
   printf("\n");
}

long isNumber(const char *s){
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}
