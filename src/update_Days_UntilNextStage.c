#include "header.h"
//----------------------------------------------------------------------------- START OF FUNCTION

// purpose: return days until next status acording to current status of node

// update_Days_UntilNextStage takes value of node status
unsigned short update_Days_UntilNextStage(unsigned short stage){
    
//temporaly value
unsigned short temp=0;

// switch statement to determin many days left until next stage of infection / recovery
// 0 days for susceptiple and for dead
    switch (stage) {
        case 0 : temp = recovery_Time; break;
        case 1 : temp = 0; break;
        case 2 : temp = exposed_Time; break;
        case 3 : temp = presymptomic_Time; break;
        case 4 : temp = infected_Mild_Time; break;
        case 5 : temp = infected_Severe_Time; break;
        case 6 : temp = infected_Critical_Time; break;
        case 7 : temp = 0; break;
  
        default: temp = 254; break;
    }
 // return assigned value   
    return temp;
    //----------------------------------------------------------------------------- END OF FUNCTION
}
