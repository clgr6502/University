#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/type.h>
#include <sys/stat.h>
#include <dirent.h>

void myfind(char *dir, char *file, char *path, int *flag);

int main(int argc, char **argv){
   int flag = 0;
   if(argc < 3){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }
 
   struct stat stbuf;

   if(stat(argv[1], &stbuf) == -1){
      printf("Errore: non è una directory\n");
      exit(1);
   }

   DIR *dfd;
   Dirent *dp;

   if((dfd = opendir(argv[1])) == NULL){
      printf("Impossibile aprire la directory\n");
      exit(1);
   }

   char *path = malloc(512);

   for(int i = 2; i < argc; i++){
      while((dp = readdir(dfd) != NULL){
         if(strcmp(dp->name, "..") == 0 ||
            strcmp(dp->name,  ".") == 0){
            continue;
         }else if(!S_ISDIR(stbuf.st_mode)){
            if(strcmp(dp->name, argv[i]) == 0){
               getcwd(path, 512);
               flag = 1;
            }
         }else{
            myfind(dp->name, argv[1], &path, &flag);
         }
      }
   }

   if(flag)
      printf("%s\n", path);
   else
      printf("File non trovato\n");

   free(path);
   closedir(dp);

   return 0;
}

void myfind(char *dir, char *file, char *path, int flag){
   struct stat stbuf;

   if(stat(dir, &stbuf) == -1){
      printf("Errore: non è una directory\n");
      exit(1);
   }

   DIR *dfd;
   Dirent *dp;

   if((dfd = opendir(dir)) == NULL){
      printf("Impossibile aprire la directory\n");
      exit(1);
   }

   char *path = malloc(512);

   while((dp = readdir(dfd) != NULL){
      if(strcmp(dp->name, "..") == 0 ||
         strcmp(dp->name,  ".") == 0){
         continue;
      }else if(!S_ISDIR(stbuf.st_mode)){
         if(strcmp(dp->name, file) == 0){
            getcwd(path, 512);
            *flag = 1;
         }
      }else{
         myfind(dp->name, file, path, *flag);
      }
   }
   return;
}
