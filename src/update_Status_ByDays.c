#include "header.h"
#include <time.h>
#include <stdlib.h>                                                             
#include <stdio.h> 


int rand();


int calculate_Propability(PERSON *f_person_P);

//-------------------------------------------------------------------------------------------------------- START OF FUNCTION
// purpose: update status  when current status is run out of days
//* example: node are infected for 14 days after which is usually person get recoverd or infection progressing - severe, critical or even dead

// status_Status_ByDays takes to values to represent node coordinates
void status_Status_ByDays(short unsigned i, short unsigned j){
  
//  check if days left are 0  ------------------------------------------------- NOTE check if function can be called only if days are 0
              if(world[i][j].daysLeft == 0 ){
 // if node is recovered (status 0) then set his status to susceptiple                 
                   if( world[i][j].status == 0){ 
                       future[i][j].status++; 
                       future[i][j].daysLeft = update_Days_UntilNextStage(future[i][j].status);                       
                        }
 // if node is infected at any stage (mild,severe, critical) but not dead  
                    if(world[i][j].status > 3 && world[i][j].status < 7 ){
                        
                       
// calculate propability is infection is progressing or node is recovering
                        if(calculate_Propability(&future[i][j])){
                                 future[i][j].status++; 
                                 future[i][j].daysLeft = update_Days_UntilNextStage(future[i][j].status);
                            }
                             else{
                                 future[i][j].status = 0;
                                 future[i][j].daysLeft = update_Days_UntilNextStage(future[i][j].status);
                            }                        
                    }
                        
// if node exposed or presimptomic progress infection to next stage and update days depending of that stage
                    else if(  world[i][j].status == 3 ||  world[i][j].status == 2  ) {  
                      future[i][j].status++; future[i][j].daysLeft =  update_Days_UntilNextStage( future[i][j].status);  
                    }
                    
                   
            } 
// if days left not 0 - reduce days value by one 
            else{
                    future[i][j].daysLeft--;     // reduce days left
                }
//----------------------------------------------------------------------------- END OF  FUNCTION        
        }
  //-------------------------------------------------------------------------------------------------------- START OF calculate_Propability FUNCTION   
  
// purpose: calculate propability of infection progress depending on current status

// calculate_Propability takes person structure 
  int calculate_Propability(PERSON *f_person_P){
      int temp = 0;     
   
      
      switch (f_person_P->status){
            case 4 : if (5 > (rand() % 10) ){temp = 1;} else {temp = 0;} break;
            case 5 : if (3 > (rand() % 10) ){temp = 1;} else {temp = 0;} break;
            case 6 : if (2 > (rand() % 10 )){temp = 1;} else {temp = 0;} break;
            default : temp = 0;
    }
      

 return temp;
 //----------------------------------------------------------------------------- END OF calculate_Propability FUNCTION
                }
