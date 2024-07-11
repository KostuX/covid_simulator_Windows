
#include <stdio.h>
#include <time.h>
#include "header.h"

int rand();
int srand();

//---------------------------------------------------------------------------------------- START OF FUNCTION
// purpose is change random  node status from suseptable to infected
void initial_Infection(){
    
//  get random coordinates 
    int hRand = rand() % hSize;
    int vRand = rand() % vSize;

// if node at generated coordinates are suseptable, change status to infected
    if(world[hRand][vRand].status == 1 )
    {
           world[hRand][vRand].status = 2;       
    }
    //---------------------------------------------------------------------------------------- END OF FUNCTION
}
