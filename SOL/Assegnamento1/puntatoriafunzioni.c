#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define OPT 4

int arg_n(const char *arg);
int arg_m(const char *arg);
int arg_o(const char *arg);
int arg_h(const char *arg);

long isNumber(const char *s);

int main(int argc, char* argv[]) {
   if(argc == 1){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }
  
   /*TIPO (nome*[N])(argomenti) = {f1, f2, fn};*/
   int(v*[OPT])(const char *arg) = {arg_h, arg_m, arg_n, arg_o};
   int opt;
 
   while ((opt = getopt(argc,argv, "n:m:o:h")) != -1) {
      switch(opt) {
         case '?':
            printf("Parametro sconosciuto\n");
         break;
         default:
         // invocazione della funzione di gestione passando come parametro l'argomento restituito da getopt
            if (V[opt%4]( (optarg==NULL ? argv[0] : optarg) ) == -1) {
               printf("Invalid argument\n");
               exit(1);
            }
         break;
      }
   }
   printf("\n");
   return 0; 
}


int arg_n(const char *arg){
   long n = isNumber(arg);
   if(n != -1){
      printf("%ld ", n);
      return 0;
   }else{
      printf("Not a number ");
      return -1;
   }
}

int arg_m(const char *arg){
   return arg_n(arg);
}

int arg_o(const char *arg){
   if(arg == NULL || arg[0] == '\0'){
      printf("Stringa vuota\n");
      return -1;
   }else{
      printf("%s ", arg);
      return 0;
   }
}

int arg_h(const char *arg){
   printf("TODO: Messaggio di aiuto\n");
   return 0;
}

long isNumber(const char* s){
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}
