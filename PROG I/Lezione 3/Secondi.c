#include <stdio.h>
int main(){
   int s = 0, m = 0, o = 0;
  
   if(scanf("%d", &s) != 1 || s < 0){
      printf("invalid input\n");
   }
   else{
      while(s >= 60){
         m += 1;
         if(m >= 60){
            o += 1;
            m -= 60;
            s -= 60;
         }
         else{
            s -= 60;
         }
      }
      printf("%d h %d min %d s\n", o, m ,s);
   }
   return 0;
}