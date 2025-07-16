#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/* 
   This code will generate a big file full of random integers. It's is useful for testing parallel aplications.
   The first argument is the number of integers. The second is the filename.
*/

int main(int argc, char *argv[]){

   if (argc < 3) { 
      printf("Usage: ./<prog> numberofints filename.\n");
      exit(1);
   }
   
   int numberOfInts = atoi(argv[1]);
   char filename[100];
   strcpy(filename, argv[2]);
   
   printf("Number Of Integers: %d, Filename: %s.\n", numberOfInts, filename);
   
   srand(time(0));

   int i;
   FILE *file = fopen(filename,"a+");
   for (i = 0; i < numberOfInts; i++) {
      int i = rand();
      fwrite(&i, sizeof(int), 1, file);
   }

   fclose(file);
   return 0;
}


