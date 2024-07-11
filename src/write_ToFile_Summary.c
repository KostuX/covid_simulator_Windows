#include "header.h"
#include <stdio.h>





void write_To_File_Summary( int cicle){
    int r=0,s=0,e=0,p=0,im=0,is=0,ic=0,d=0;

    for (int ii = 0; ii < vSize; ++ii) {
        for (int j = 0; j < hSize; ++j) {

            switch (world[ii][j].status) {
                case 0: {r++;  break;} // recovered
                case 1: {s++;  break;} // susceptiple
                case 2: {e++;  break;} // Exposed
                case 3: {p++;  break;} // Presimtomic
                case 4: {im++;  break;} // Infected(Mild)
                case 5: {is++;  break;} // Infected(Severe)
                case 6: {ic++;  break;} // Infected(Critical)
                case 7: {d++;  break;} // Dead
            }

        }

    }


    FILE * file_summary = fopen("output//world_Summary.dat","a"); // W crate file and write, R read file, A append to file


    if(file_summary == NULL){printf("error opening file");}

    fprintf(file_summary, "%d %d %d %d %d %d %d %d %d\n",cicle, r, s, e, p, im, is, ic, d);
    fclose(file_summary);

    // printf("Susceptiple= %d,\t Exposed= %d,\t Infected= %d,\t Removed= %d\n",s,e,i,r);



}
