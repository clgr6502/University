#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define K1 100
#define K2 120

int main(int argc, char **argv){
   int n, k1, k2;

   if(argc == 4){
      n = (int) atoi(argv[1]);
      k1 = (int) atoi(argv[2]);
      k2 = (int) atoi(argv[3]);

      if(k1 >= k2){
         printf("Errore, k1 deve essere minore di k2.\n");
         exit(1);
      }
   }else if(argc > 1 && argc < 4){
      printf("Numero di argomenti insufficiente.\n");
      exit(1);
   }else{
      n = N;
      k1 = K1;
      k2 = K2;
   }

   //per il seme di rand_r
   unsigned int seed = time(NULL);
   int num, siz = k2 - k1;
   int arr[siz];

   for(int i = 0; i < siz; i++){
      arr[i] = 0;
   }

   //NOTA: intervallo [k1, k2[
   //per intervallo chiuso: k1 + rand_r(&seed) % (k2 - k1 + 1)
   for(int i = 0; i < n; i++){
      num = k1 + rand_r(&seed) % (k2 - k1);
      arr[num % siz]++;
   }
   int j = 0;
   for(int i = k1; i < k2 && j < n; i++){
      printf("[%d]: %2.2f\n", i, (float)arr[j] * (float) siz / 100);
      j++;
   }

   return 0;
}
