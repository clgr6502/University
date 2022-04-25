#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define dimN 16
#define dimM  8

#define PRINTMAT(mat, dimN, dimM)         \
   for(int i = 0; i < dimN; i++){         \
      for(int j = 0; j < dimM; j++){      \
         printf("%2ld ", ELEM(mat, i, j));\
      }                                   \
      printf("\n");                       \
   }

#define CHECK_PTR_EXIT(ptr, str) \
   if(ptr == NULL){ \
      perror(str);  \
      EXIT_FAILURE; \
   }

#define ELEM(m, i, j) (m + i)[j]

int main(){
   long *M = malloc(dimN*dimM*sizeof(long));
   CHECK_PTR_EXIT(M, "malloc");

   for(size_t i = 0; i < dimN; ++i){
      for(size_t j = 0; j < dimM; ++j){
         ELEM(M,i,j) = i + j;
      }
   }

   PRINTMAT(M, dimN, dimM);
   free(M);
   return 0;
}
