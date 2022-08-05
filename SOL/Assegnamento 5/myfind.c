#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <error.h>

#define MAX 128

void myfind(char *dir, char *file, char *path, int *flag, char *lc);
int isFile(struct stat buf);
int isDir(struct stat buf);

int main(int argc, char **argv){
   int flag = 0;
   char *lc = malloc(MAX);

   if(argc < 3){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }

   char *path = malloc(MAX);

   for(int i = 2; i < argc; i++){
      flag = 0;
      myfind(argv[1], argv[i], path, &flag, lc);

      printf("----------\n");
      if(flag){
         printf("Trovato %s: %s\n", argv[i], path);
         printf("Ultima modifica: %s", lc);
      }else{
         printf("%s non trovato\n", argv[i]);
      }
   }

   free(path);
   free(lc);

   return 0;
}

void myfind(char *dir, char *file, char *path, int *flag, char *lc){
   //Per caricare i dati del file/directory
   struct stat stbuf;
   struct stat st;

   char *atDir = malloc(MAX);

   if(stat(dir, &stbuf) == -1){
      perror("Errore");
      exit(1);
   }

   char *nome = malloc(MAX);
   char *perc = malloc(MAX);
   char *prev = malloc(MAX);

   DIR *dfd;
   struct dirent *dp;

   if((dfd = opendir(dir)) == NULL){
      perror("Impossibile aprire la directory");
      exit(1);
   }

   chdir(dir);

   while((dp = readdir(dfd)) != NULL){
      strcpy(nome, dp->d_name);
      getcwd(atDir, MAX);

      if(stat(nome, &st) != -1){
         if(strcmp(nome, "..") == 0 ||
            strcmp(nome,  ".") == 0){
            continue;
         }else if(isDir(st)){
            myfind(nome, file, path, flag, lc);
         }else{
            if(strcmp(nome, file) == 0){
               *flag = 1;
               sprintf(lc, "%s", ctime(&st.st_mtime));
               sprintf(path, "%s/%s", atDir, file);

               chdir("..");
               closedir(dfd);
               free(nome);
               free(perc);
               free(atDir);
               free(prev);

               return;
            }
         }
      }
   }
   chdir("..");

   closedir(dfd);
   free(nome);
   free(perc);
   free(atDir);
   free(prev);

   return;
}

int isDir(struct stat buf){
   if(S_ISDIR(buf.st_mode)){
      return 1;
   }
   return 0;
}
