
#include <stdio.h>


#include "header.h"
int rand();

PERSON 
future[vSize][hSize], 
world[vSize][hSize];

//---------------------------------------------------------------------------------------- START OF FUNCTION
// purpose: populate world with initial values
// default values are 
// status = 1; suseptable
// daysLeft = 0; days until change in health status
// surrSick = 0; infected eighbours
// age = random number between 0-100
void populate(){       

    for (int i = 0; i < vSize; ++i) {       
        
        for (int j = 0; j < hSize; ++j) {
            
            world[i][j].status = 1;
            world[i][j].daysLeft = 0;
            world[i][j].surrSick = 0;
            world[i][j].age =  (rand()%100);
            
// copy same values to future world            
       future[i][j] = world[i][j];
 
        }
    }
    //---------------------------------------------------------------------------------------- END OF FUNCTION
}
