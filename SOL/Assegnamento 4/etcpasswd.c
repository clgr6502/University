#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(int argc, char **argv){
   FILE *pwd = fopen("/etc/passwd", "r");

   if(pwd == NULL){
      printf("Errore nell'apertura del file.\n");
      exit(1);
   }

   FILE *dmp;
   if(argc == 2){
      dmp = fopen(argv[1], "w");
      if(dmp == NULL){
         printf("Errore nella creazione del file.\n");
         exit(1);
      }
   }else{
      printf("Utilizzo: ./a.out nomefile\n");
      exit(1);
   }

   char *user = malloc(sizeof(char*) * MAX);
   char *buf;

   fgets(user, MAX, pwd);

   do{
      char *lenmax = strchr(user, ':');
      buf = malloc(strlen(user));

      for(int i = 0; i < strlen(user); i++){
          if(&user[i] != lenmax){
             buf[i] = user[i];
          }else{
             buf[i] = '\n';
             break;
          }
      }
      fgets(user, MAX, pwd);

      fprintf(dmp, "%s", buf);
   }while(!feof(pwd));

   free(user);
   free(buf);
   fclose(pwd);
   fclose(dmp);

   return 0;
}
