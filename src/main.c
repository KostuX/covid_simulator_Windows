

#include <windows.h>
#include <stdio.h>

#include "header.h"
#include "populate.c"

#include "initial_Infection.c"
#include "getSickNeighbours.c"

#include "spread_infection.c"
#include "update_Status_ByDays.c"
#include "update_Days_UntilNextStage.c"
#include "write_ToFile_Summary.c"
#include "write_toFile_World.c"

#define MAX_THREADS 4
HANDLE hMutex;
DWORD WINAPI P_Main(LPVOID lpParam);

typedef struct MyData
{
    int currentThread;

} MYDATA, *PMYDATA;

// Variable declarations
//----------------------------------------------------- VARIABLES
int thread_counter = 0;

unsigned short
    cicle_Limit = 1000,
    cicle = 0;

unsigned char
    recovery_Time = 180,
    exposed_Time = 3,
    presymptomic_Time = 7,
    infected_Mild_Time = 10,
    infected_Severe_Time = 10,
    infected_Critical_Time = 13;

short unsigned currLine = 0;

double elapsedTime;
void printSystemTime(SYSTEMTIME st)
{
    printf("Date: %02d/%02d/%04d\n", st.wDay, st.wMonth, st.wYear);
    printf("Time: %02d:%02d:%02d.%03d\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}

// p_Main() -  is core function where most of calculation done
// updates status ByDays, gets infected neighbours, spread infection, copy data from future to current world

DWORD WINAPI P_Main(LPVOID lpParam)
{
    WaitForSingleObject(hMutex, INFINITE);
    PMYDATA pDataArray;

    pDataArray = (PMYDATA)lpParam;

    // make thread count from 1 (not 0)
    long thread_Nr = (long)pDataArray->currentThread + 1;

    // calculate tasks per thread
    unsigned short
        vTask_Size = vSize / MAX_THREADS,
        hTask_Size = hSize / MAX_THREADS;

    // assing task / lines to be processed by individual thread
    unsigned short
        z,
        x,
        bottom = ((thread_Nr)-1) * hTask_Size,
        top = (((thread_Nr)*hTask_Size));

    // if its the last thread ensure that it have reached final line in world
    if (thread_Nr == MAX_THREADS)
    {
        top = vSize;
    }

    while (cicle < cicle_Limit)
    {
        // add infection every 10th cycle

        if (cicle % 10 == 0 && (thread_Nr == MAX_THREADS))
            initial_Infection();

        for (x = 0; x < vSize; x++)
        {
            for (z = bottom; z < top; z++)
            {
                status_Status_ByDays(x, z);
                getSickNeighbours(x, z);
                spread_Infection(x, z);
            }
        }

        thread_counter++;
        if (thread_counter == MAX_THREADS)
        {

            for (x = 0; x < vSize; x++)
            {
                for (z = 0; z < hSize; z++)
                {
                    world[x][z] = future[x][z];
                }
            }

            // Write data to files
            // write_To_File_World() - writes data to be displayed as visualisation of infection spread
            // write_To_File_Summary - summarised data for representation in chart
            write_To_File_World();
            write_To_File_Summary(cicle);
            thread_counter = 0;

            cicle++;
        }
    }
    ReleaseMutex(hMutex);
}

int main(int argc, char *argv[])
{
    SYSTEMTIME t1, t2;
    GetSystemTime(&t1);
    printSystemTime(t1);

    PMYDATA pDataArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS];

    hMutex = CreateMutex(NULL, FALSE, NULL);

    populate();

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                           sizeof(MYDATA));

        pDataArray[i]->currentThread = i;

        hThreadArray[i] = CreateThread(
            NULL,                 // default security attributes
            0,                    // use default stack size
            P_Main,               // thread function name
            pDataArray[i],        // argument to thread function
            0,                    // use default creation flags
            &dwThreadIdArray[i]); // returns the thread identifier
    }

    // Wait until all threads have terminated.
    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
        if (pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL; // Ensure address is not reused.
        }
    }

    /*
               gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;    // sec to ms
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
            printf("\ntime elapsed: %f ms.\n", elapsedTime);

        */

    CloseHandle(hMutex);

    printf("All threads have finished execution.\n");
    // return 0 if lucky
    return 0;

} //---------------------------------------------------------------------------------------- END OF MAIN
