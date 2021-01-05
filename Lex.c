/***********************************************************************
* Maria Fernanda Becerra, mfbecerr
* CSE101
* PA1
* Lex.c
***********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160
int main(int argc, char * argv[]){

   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: Lex <input file> <output file>\n");
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
   char temp;
   int n=0;
   while((temp=fgetc(in))!=EOF){
     if(temp=='\n'){
       n++;
     }
   }
   rewind(in);
   char** A=calloc(n,sizeof(char*));
   for (int i=0;i<n;i++){
     A[i]=calloc(100,sizeof(char));
     fgets(A[i],200,in);
   }
   List L= newList();
   prepend(L,0);
   for(int i=1;i<n;i++){
     moveFront(L);
     while(index(L)>=0 && (strcmp(A[get(L)],A[i])<0)){
       moveNext(L);
//       printf("%d",index(L));
     }
     if(index(L)==-1){
       append(L,i);
     }
     else{
       insertBefore(L,i);
     }
   }
   for(moveFront(L);index(L)>=0;moveNext(L)){
     fprintf(out,"%s",A[get(L)]);
   }

    
   fclose(in);
   fclose(out);
   for(int i=0;i<n;i++){
     free(A[i]);
   }
   free(A);
   freeList(&L);

   return(0);
}
