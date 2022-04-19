#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   if(argc != 3){
      fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
      return -1;
   }

   char *buf1 = NULL;
   char *buf2 = NULL;

   char* token1 = strtok_r(argv[1], ".", &buf1);

   while(token1){
      printf("%s ", token1);
      token1 = strtok_r(NULL, ".", &buf1);
   }

   char* token2 = strtok_r(argv[2], ".", &buf2);

   while(token2){
      printf("%s ", token2);
      token2 = strtok_r(NULL, ".", &buf2);
   }
   printf("\n");
   return 0;
}
