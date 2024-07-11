 
CC = gcc

CFLAG =  

OUTPUT_FILE = all.out

ERR_LOG = 2> ERR_LOG.log

LIST = ./src/main.c  \
	./src/header.h \
	./src/populate.c \
	./src/initial_Infection.c \
	./src/getSickNeighbours.c \
	./src/spread_Infection.c \
	./src/update_Days_UntilNextStage.c \
	./src/update_Status_ByDays.c \
	./src/write_ToFile_Summary.c \
	./src/write_ToFile_World.c  
 
parallel: ./src/main.c 
	$(CC) $(CFLAG) $(LIST) $(ERR_LOG) -o $(OUTPUT_FILE) -lpthread
	
serial: ./src/main.c 
	$(CC) $(CFLAG) $(LIST) $(ERR_LOG) -o $(OUTPUT_FILE)



obj: ./src/main.c 
	$(CC) $(CFLAG) -c $(LIST) 

	
clean: 
	rm   \
	*.o  \
	$(OUTPUT_FILE) 
