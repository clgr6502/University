//W I P
//Da modificare (vedere "myfind.c")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MAX 512

void copy(char *file1, char *file2, int bufff);
void subdir(char *sub, char *dst, int bufff);

int main(int argc, char **argv){
printf("main\n");
   int bufff;

   if(argc < 3){
      printf("Argomenti insufficienti\n");
      exit(1);
   }else if(argc == 4){
       bufff = atoi(argv[3]);
   }else{
       bufff = MAX;
   }

   DIR *src, *dst;

   if((src = opendir(argv[1])) == NULL){
      perror("Errore apertura sorgente\n");
      exit(1);
   }

   if((dst = opendir(argv[2])) == NULL){
      perror("Errore apertura destinazione\n");
      exit(1);
   }

   struct dirent *entry1;
   struct stat st;

   char *path1 = malloc(bufff);
   char *path2 = malloc(bufff);

   char *percorso = malloc(bufff);

   while((entry1 = readdir(src)) != NULL){
      getcwd(percorso, bufff);

      sprintf(path1, "%s/%s%s", percorso, argv[1], entry1->d_name);
      sprintf(path2, "%s/%s%s", percorso, argv[2], entry1->d_name);

      if(strcmp(entry1->d_name, "." ) == 0 ||
         strcmp(entry1->d_name, "..") == 0){
         continue;
      }else{
          if(stat(path1, &st) == 0){
            if(S_ISREG(st.st_mode)){
               copy(path1, path2, bufff);
            }else if(S_ISDIR(st.st_mode)){
               subdir(path1, path2, bufff);
            }
         }
      }
   }

   free(path1);
   free(path2);
   free(percorso);
   
   closedir(src);
   closedir(dst);
   return 0;
}

void copy(char *file1, char *file2, int bufff){
   int fd1, fd2, size, n;
   char *stringa = malloc(bufff);

   if((fd1 = open(file1, O_RDWR, 0)) == -1){
      perror("Errore apertura file\n");
      exit(1);
   }

   size = lseek(fd1, 0, SEEK_END);
   lseek(fd1, 0, SEEK_SET);

   if((fd2 = creat(file2, /*O_CREAT | O_WRONLY*/ 0666)) == -1){
      perror("Errore apertura file\n");
      exit(1);
   }

   while((n = read(fd1, stringa, bufff)) > 0){
      if(write(fd2, stringa, bufff) != -1){
         perror("Errore durante la copia\n");
         exit(1);
      }
   }
   close(fd1);
   close(fd2);
}

void subdir(char *sub, char *sdst, int bufff){
printf("subdir\n");

   DIR *src;
   int dst;

   if((src = opendir(sub)) == NULL){
      printf("errore apertura directory src\n");
      exit(1);
   }
   if((dst = mkdir(sdst, 0777)) == -1){
      printf("errore creazione cartella\n"); 
      exit(1);
   }
   struct dirent *entry1;
   struct stat st;

   char *path1 = malloc(bufff);
   char *path2 = malloc(bufff);

   char *percorso = malloc(bufff);

   while((entry1 = readdir(src)) != NULL){
      getcwd(percorso, bufff);

      sprintf(path1, "%s/%s", sub, entry1->d_name);
      sprintf(path2, "%s/%s", sdst, entry1->d_name);

      if(strcmp(entry1->d_name, "." ) == 0 ||
         strcmp(entry1->d_name, "..") == 0){
         continue;
      }else{
          if(stat(path1, &st) == 0){
            if(S_ISREG(st.st_mode)){
               copy(path1, path2, bufff);
            }else if(S_ISDIR(st.st_mode)){
               subdir(path1, path2, bufff);
            }
         }
      }
   }
   
   free(path1);
   free(path2);
   free(percorso);
   
   closedir(src);

   return;
}
