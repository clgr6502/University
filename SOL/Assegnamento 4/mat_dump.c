#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void confronta(int (*fun)(const void*, const void*, size_t),
    float *m1, float *m2, size_t n);

int main(int argc, char **argv){
   int n;
   if(argv[1] != NULL){
      n = atoi(argv[1]);
   }else{
      printf("Errore\n");
      exit(1);
   }

   FILE *bin;
   FILE *txt;

   if(argc == 4){
      bin = fopen(argv[2], "rb");
      txt = fopen(argv[3], "r");
   }else{
      bin = fopen("mat_dump.dat", "wb");
      txt = fopen("mat_dump.txt", "w");
   }

   float M1[n][n];
   float M2[n][n];

   float x;

   if(argc != 4){
      char space = ' ';
      char nl = '\n';
      for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
            M1[i][j] = (i + j) / 2.0;

            x = M1[i][j];

            fwrite(&x, n, sizeof(float), bin);
            fwrite(&space, 1, sizeof(char), bin);

            fprintf(txt, "%2.2f ", x);
         }
         fwrite(&nl, 1, sizeof(char), bin);
         fprintf(txt, "\n");
      }
   }else{
      for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
            fread(&M1[i][j], 1, sizeof(float), bin);
            fscanf(txt, "%f", &M2[i][j]);
         }
      }
      confronta(memcmp, *M1, *M2, n);
   }

   fclose(bin);
   fclose(txt);

   return 0;
}

void confronta(int (*fun)(const void*, const void*, size_t),
   float *m1, float *m2, size_t n){

   printf("%d\n", fun(m1, m2, n));
   return;
}
