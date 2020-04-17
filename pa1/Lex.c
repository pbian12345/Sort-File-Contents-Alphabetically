
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 1600

int main(int argc, char * argv[]){

   int n, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
    //   n = 0;
      token = strtok(line, " \n");
      tokenlist[0] = '\0';
      while( token!=NULL ){
        //  strcat(tokenlist, "   ");
         strcat(tokenlist, token);
        //  strcat(tokenlist, "\n");
        //  n++;
         token = strtok(NULL, " \n");
      }
    //   fprintf(out, "line %d contains %d token%s: \n", count, n, n==1?"":"s");
    //   fprintf(out, "%s\n", tokenlist);
   }

   List result = newList();
   for (int i = 1; i < count; i++){
      moveFront(result);
      while (index(result) >= 0){
         if (strcmp(tokenlist[i], tokenlist[get(result)]) < 0){
            insertBefore(result, i);
            moveBack(result);
            moveNext(result);
         }
         else{
            if ((length(result) - index(result)) == 1){
               insertAfter(result, i);
               moveNext(result);
            }
            moveNext(result);
         }
      }
   }

   printList(out, result);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}