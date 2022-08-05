#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <error.h>

#define MAX 128

void myfind(char *dir, char *file, char *path, int *flag);
int isFile(struct stat buf);
int isDir(struct stat buf);

int main(int argc, char **argv){
   int flag = 0;

   if(argc < 3){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }

   char *path = malloc(MAX);

   for(int i = 2; i < argc; i++){
      flag = 0;
      myfind(argv[1], argv[i], path, &flag);

      if(flag){
         printf("Trovato %s: %s\n", argv[i], path);
      }else{
         printf("%s non trovato\n", argv[i]);
      }
      printf("------------\n");
   }

   free(path);

   return 0;
}

void myfind(char *dir, char *file, char *path, int *flag){
   //Per caricare i dati del file/directory
   struct stat stbuf;
   struct stat st;

printf("<%s>\n", dir);
   char *atDir = malloc(MAX);
   sprintf(atDir, "%s/%s", getcwd(atDir, MAX), dir);

printf("[%s]\n", atDir);
   if(stat(atDir, &stbuf) == -1){
      perror("Errore");
      exit(1);
   }

   char *nome = malloc(MAX);
   char *perc = malloc(MAX);

   DIR *dfd;
   struct dirent *dp;

   if((dfd = opendir(atDir)) == NULL){
      perror("Impossibile aprire la directory");
      exit(1);
   }

   while((dp = readdir(dfd)) != NULL){
      strcpy(nome, dp->d_name);
      sprintf(perc, "%s/%s", dir, nome);

      if(stat(perc, &st) != -1){
         if(strcmp(nome, "..") == 0 ||
            strcmp(nome,  ".") == 0){
            continue;
         }else if(isDir(st)){
            sprintf(perc, "%s/%s", atDir, nome);
printf("%s\n", perc);
chdir(perc);
            myfind(nome, file, path, flag);
         }else{
            if(strcmp(nome, file) == 0){
               *flag = 1;
               sprintf(path, "%s/%s", atDir, file);
               return;
            }
         }
      }
   }

   closedir(dfd);
   free(nome);
   free(perc);
   free(atDir);

   return;
}

int isDir(struct stat buf){
   if(S_ISDIR(buf.st_mode)){
      return 1;
   }
   return 0;
}
