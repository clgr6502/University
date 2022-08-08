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

#include <pwd.h>
#include <grp.h>

#define MAX 32

void prtAttr(char *nome);
char *perm(char *per, struct stat buf);

int main(int argc, char **argv){

   for(int i = 1; i < argc; i++){
      prtAttr(argv[i]);
   }

   return 0;
}

void prtAttr(char *nome){
   int fd;
   struct stat st;
   DIR *dfd;
   struct dirent *dp;

   char per[10];

   char *modo = malloc(MAX);

   if((fd = open(nome, O_RDONLY, 0)) == -1){
      perror("Open");
      exit(1);
   }

   if(stat(nome, &st) == -1){
      perror("fstat\n");
      exit(1);
   }

   if(S_ISDIR(st.st_mode)){
      strcpy(modo, "Directory");
   }else if(S_ISREG(st.st_mode)){
      strcpy(modo, "File");
   }

   
   printf("[%s]\n", nome);
   printf("\t#inode:\t%ld\n\tType:\t%s\n", st.st_ino, modo);
   printf("\tPerms:\t%s\n\tUID:\t%d\n", perm(per, st), getpwuid(st.st_uid)->pw_uid);
   printf("\tGID:\t%d\n\tDim:\t%ld\n", getgrgid(st.st_gid)->gr_gid, st.st_size);
   printf("\tLastMod: %s\n", ctime(&st.st_mtime));
   free(modo);
   close(fd);
}

char *perm(char *per, struct stat buf){
   per[0] = (S_ISDIR(buf.st_mode) ? 'd': '-');
   per[1] = ((buf.st_mode & S_IRUSR) ? 'r' : '-');
   per[2] = ((buf.st_mode & S_IWUSR) ? 'w' : '-');
   per[3] = ((buf.st_mode & S_IXUSR) ? 'x' : '-');
   per[4] = ((buf.st_mode & S_IRGRP) ? 'r' : '-');
   per[5] = ((buf.st_mode & S_IWGRP) ? 'w' : '-');
   per[6] = ((buf.st_mode & S_IXGRP) ? 'x' : '-');
   per[7] = ((buf.st_mode & S_IROTH) ? 'r' : '-');
   per[8] = ((buf.st_mode & S_IWOTH) ? 'w' : '-');
   per[9] = ((buf.st_mode & S_IXOTH) ? 'x' : '-');
//Non necessario
   return per;
}
