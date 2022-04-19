#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPT 4

int arg_n(const char *arg);
int arg_m(const char *arg);
int arg_o(const char *arg);
int arg_h(const char *arg);

long isNumber(const char *s);

int main(int argc, char **argv){
   if(argc == 1){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }


   /*TIPO (nome*[N])(argomenti) = {f1, f2, ...,fn};*/
   int (*funz[4])(const char *) = {arg_h, arg_m, arg_n, arg_o};
   int opt;


   while((opt = getopt(argc, argv, "n:m:o:h")) != -1){
      switch(opt){
         case '?':
            printf("Parametro non riconosciuto\n");
         break;
         default:
         // invocazione della funzione di gestione passando come parametro l'argomento restituito da getopt
            if(funz[opt % OPT]((optarg == NULL ? argv[0] : optarg))== -1){
               printf("Errore parametro ");
            }
         break;
      }
      printf("\n");
   }
   return 0;
}

int arg_n(const char *arg){
   long num;
   if((num = isNumber(arg)) != -1){
      printf("%ld ", num);
      return 0;
   }else{
      return -1;
   }
}

int arg_m(const char *arg){
   return arg_n(arg);
}

int arg_o(const char *arg){
   if(arg == NULL || arg[0] == '\0'){
      return -1;
   }else{
      printf("%s ", arg);
      return 0;
   }
}

int arg_h(const char *arg){
   printf("Utilizzo: -n <num> -m <num> -o <string> -h ");
   return 0;
}

long isNumber(const char* s) {
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}
