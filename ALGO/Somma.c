 #include <stdio.h>

int main(){
   int a, tmp;

   tmp = 0;

   do{
      scanf("%d", &a);
      tmp += a;
   }while(a != 0);

   printf("%d\n", tmp);
   return 0;
}