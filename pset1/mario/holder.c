#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

void run(int num);
void empty_space(int num);
void hash_tag(int num);

int main(int argc, char* argv[]){

   if( argc == 2){ printf("correct # of inputs\n");

    int num= -1;

    //while( !( num >= 1 && num <= 8 )  ){  num= get_int("Height: ");  }
    num = atoi( argv[1] );
    run(num);

   }
   else if( argc > 1){ printf("too many arguments provided\n");}
   else{printf("no arguments provided\n");}

   return 0;

  }

   void run( int num ){
     int symbol= -1; int space= -1;
     for( int i= 1; i<= num; i++){
         symbol= i; space= num- i;
         empty_space(space);
         hash_tag(symbol);
         printf("  ");
         hash_tag(symbol);
         printf("\n");
     }
 }

 void empty_space(int num){
     for(  int j= 1; j<= num; j++  ){
         printf(" ");
     }
 }

 void hash_tag(int num){
     for( int i= 1; i<= num; i++ ){ printf("#");}

 }