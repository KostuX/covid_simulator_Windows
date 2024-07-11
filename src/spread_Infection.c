#include "header.h"

int rand();
 //------------------------------------------------------------------------------------------------------------ START OF FUNCTION
// purpose: is infect node if it meet conditions 
//* is suseptable - node can get infected onlyif he not infected yet or not dead therefore only if suseptable
//* have more infected neighbours than number generated randomly 0-10) - this brings that more infected neighbours more chances to get infected up to 80%

//spread_Infection() methid takes number values representing coordinates of node to be processed
void spread_Infection(short unsigned i, short unsigned j){



// check if node is suseptable, also calculate propability to get infected acording infected neighbours count
            if(world[i][j].status == 1 && (rand()%10) < world[i][j].surrSick) {
                
// change status to exposed
                future[i][j].status = 2;
// set days left until status chaged to presimptomic
                future[i][j].daysLeft =  update_Days_UntilNextStage(future[i][j].status);
            }
//------------------------------------------------------------------------------------------------------------ END OF FUNCTION
}
      
