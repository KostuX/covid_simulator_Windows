#include "header.h"


//---------------------------------------------------------------------------------------- START OF FUNCTION
// get getSickNeighbours() takes two parameters as coordinates of node which has to be checked
// purpose is to get count of infected neighbours 

void getSickNeighbours( short unsigned i, short unsigned j){
    
    if(world[i][j].status == 1){

// reset counters
            world[i][j].surrSick = 0;
            future[i][j].surrSick = 0;
            
// loop your neighbours
            
            for (int k = i-1; k < i+2; ++k) {
                for (int l = j-1; l < j+2; ++l) {
                    
// skip current node ( dont count myself as treat to myself)
                 //   if(i==k && j==l){ continue;} 
                    
// when reached boudries check other side of the  world 
                    int x = l >= 0? l%hSize : hSize+(l);              
                    int xx = k >= 0? k%vSize : vSize+(k);

// if neighbour staus is between recovered or dead incriment counter by one
                    if(world[xx][x].status > 2 && world[xx][x].status < 7 ) {world[i][j].surrSick++; } 
                   // if(future[xx][x].status > 2 && future[xx][x].status < 7 ) {future[i][j].surrSick++;} 
                }
            }
    }
//---------------------------------------------------------------------------------------- END OF FUNCTION
}
