#include <stdio.h>

int main(void){
   int digits=0; int remainder= 0;
   int num= 123;

   printf( "%i\n", num );
   while( num != 0 ){
   digits+= num%10;
   num/=10;
   }
   printf( "sum %i", digits);

}