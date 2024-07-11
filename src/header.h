#ifndef HEADER_H
#define HEADER_H

#define vSize 100
#define hSize 100

extern unsigned short
cicle_Limit,
cicle;



 typedef struct person {     
 
   unsigned char    
   surrSick,
   status,
   daysLeft,
   age;
   
} PERSON;

extern PERSON 
future[vSize][hSize], 
world[vSize][hSize];


extern unsigned char
recovery_Time,
exposed_Time,
presymptomic_Time,
infected_Mild_Time,
infected_Severe_Time,
infected_Critical_Time;
 

void populate();
void initial_Infection();
void status_Status_ByDays(short unsigned i, short unsigned j);

void getSickNeighbours(short unsigned i, short unsigned j);

unsigned short update_Days_UntilNextStage(unsigned short stage);
void spread_Infection(short unsigned i, short unsigned j);
void write_To_File_World();
void write_To_File_Summary(int cicle);




#endif
