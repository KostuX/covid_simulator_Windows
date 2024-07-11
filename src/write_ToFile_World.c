#include "header.h"
#include <stdio.h>

unsigned short 
file_Nr = 0;

PERSON **arr[100];


void write_To_File_World(){
    
    //arr[0] = world;
    
   
    char filename[100] = "world";

    snprintf(filename, sizeof(filename), "output/world_Data/%d.dat", file_Nr++);
    FILE *file_out = fopen(filename, "w");
    

   if(file_out == NULL){printf("error opening file");}

    for (int i = 0; i < vSize; ++i) {
        for (int j = 0; j < hSize; ++j) {
          fprintf(file_out, "%d %d %d \n",i,  j, world[i][j].status);
          //      fprintf(file_out, "%u %u %u\n",(unsigned short)i, (unsigned short) j, (char)world[i][j].status);

        }
    }
    fclose(file_out);
}
