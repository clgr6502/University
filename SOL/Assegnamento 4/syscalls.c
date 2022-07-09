#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
//#include "syscalls.h"

int main(int argc, char **argv){
   if(argc < 3){
      printf("Troppi pochi argomenti\n");
      exit(1);
   }

   errno = 0 //?
   DIR *src = opendir("./"argv[1]);
   DIR *dst = opendir("./"argv[2]);

   if(src == NULL){
      printf("Errore: directory non trovata\n");
      exit(1);
   }

   if(dst == NULL){
      printf("Errore creazione directory\n");
      error(1);
   }

   dst->fd = src->fd;
   dst->Dirent = src;

   closedir(src);
   closedir(dst);

   return 0;
}