

// #include <stdio.h>
// #include <stdlib.h>
// #ifdef _WIN32
// #include <io.h>
// #define access _access

////#else
// #include <unistd.h>
/// #endif
// #include <sys/sysinfo.h>
// #include <sys/time.h>

// #include <pthread.h>

#include <windows.h>
#include <stdio.h>

#include "header.h"
#include "populate.c"

HANDLE hMutex;

// Variable declarations
//----------------------------------------------------- VARIABLES
const int MAX_THREADS = 64;
/*
void *thread_func(void *param);
long thread;
pthread_t *thread_handles;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

int thread_counter = 0;

void *p_Main(void *rank);
*/
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

int thread_count;

double elapsedTime;
void printSystemTime(SYSTEMTIME st)
{
    printf("Date: %02d/%02d/%04d\n", st.wDay, st.wMonth, st.wYear);
    printf("Time: %02d:%02d:%02d.%03d\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}

// Entry point
//----------------------------------------------------------------------------- MAIN

// p_Main() -  is core function where most of calculation done
// updates status ByDays, gets infected neighbours, spread infection, copy data from future to current world

DWORD WINAPI P_Main(LPVOID lpParam)
{
    WaitForSingleObject(hMutex, INFINITE);
    printf("Thread %d: inside critical section\n", GetCurrentThreadId());
    ReleaseMutex(hMutex);
    /*
        // make thread count from 1 (not 0)
        long thread_Nr = (long)rank + 1;

        // calculate tasks per thread
        unsigned short
            vTask_Size = vSize / thread_count,
            hTask_Size = hSize / thread_count;

        // assing task / lines to be processed by individual thread
        unsigned short
            z,
            x,
            bottom = ((thread_Nr)-1) * hTask_Size,
            top = (((thread_Nr)*hTask_Size));

        // if its the last thread ensure that it have reached final line in world
        if (thread_Nr == thread_count)
        {
            top = vSize;
        }

        while (cicle < cicle_Limit)
        {

            // add infection every 10th cycle

            if (cicle % 10 == 0 && (thread_Nr == thread_count))
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

            pthread_mutex_lock(&mutex);
            thread_counter++;
            if (thread_counter == thread_count)
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
                pthread_cond_broadcast(&cond_var);
                cicle++;
            }
            else
            {
                while (pthread_cond_wait(&cond_var, &mutex) != 0)
                {
                };
            }
            pthread_mutex_unlock(&mutex);
        }
        */
}

int main(int argc, char *argv[])
{
    SYSTEMTIME t1, t2;
    GetSystemTime(&t1);
    printSystemTime(t1);

    hMutex = CreateMutex(NULL, FALSE, NULL);
    thread_count = 4;

    populate();

    HANDLE hThread1 = CreateThread(NULL, 0, P_Main, NULL, 0, NULL);
    /*
            // create mutex for threads
            pthread_mutex_init(&mutex, NULL);

            // allocate memory for threads
            thread_handles = malloc(thread_count * sizeof(pthread_t));

            // generate data in map
            // default values are
            // status = 1; suseptable
            // daysLeft = 0; days until change in health status
            // surrSick = 0; infected eighbours
            // age = random number between 0-100
            populate();

            // create threads and execute p_Main functionn
            // p_Main() -  is core function where most of calculation done
            // updates status ByDays, gets infected neighbours, spread infection, copy data from future to current world
            for (thread = 0; thread < thread_count; thread++)
            {
                pthread_create(&thread_handles[thread], NULL, *p_Main, (void *)thread);
            }

            // set threads to wait until all have completed tasks befor continue
            for (thread = 0; thread < thread_count; thread++)
            {
                pthread_join(thread_handles[thread], NULL);
            }

            // applicatin exit procedure
            //---------------------------------------------------------------------------------------- CLOSING
            // free memory allocated to threads
            free(thread_handles);
            // destroy mutex
            pthread_mutex_destroy(&mutex);

            // pthread_exit(NULL);
            // display time

            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;    // sec to ms
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
            printf("\ntime elapsed: %f ms.\n", elapsedTime);

        */

    // Wait for both threads to finish
    WaitForSingleObject(hThread1, INFINITE);
    // WaitForSingleObject(hThread2, INFINITE);

    // Close thread and mutex handles
    CloseHandle(hThread1);

    CloseHandle(hMutex);

    printf("All threads have finished execution.\n");
    // return 0 if lucky
    return 0;

} //---------------------------------------------------------------------------------------- END OF MAIN
