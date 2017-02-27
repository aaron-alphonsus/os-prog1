/**
 * @file test.c
 * 
 * @brief Tests the implementation of the PID manager by creating 100 threads, 
 * and having each thread request a pid, sleep for a random period of time and
 * releast the pid 
 *
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */

#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "pid.h"

/// Define constants
#define NUM_THREADS 100
#define ITERATIONS   10
#define SLEEP         5

/// Declare in_use array
int in_use[PID_MAX + 1];

/**
 * mutex lock used when accessing data structure
 * to ensure there are no duplicate pid's in use.
 */
pthread_mutex_t test_mutex;

/**
 * This function defines the test strategy. Each thread requests a pid to be 
 * allocated, sleeps for a random period of time and then releases it. The pid
 * allocated and released is printed. If no pid is available, a message is
 * displayed.
 *
 * @param[in] param Void pointer 
 */
void *allocator(void *param)
{
    /// Declare local variables
    int i, pid;

    /// Iterate ITERATIONS times
    for (i = 0; i < ITERATIONS; i++) {
        
        /// Sleep for a random period of time
        sleep( (int)(random() % SLEEP) );

        /// Allocate a pid
        pid = allocate_pid();
        
        /// If pid = -1, no pid available
        if (pid == -1)
            printf("No pid available\n");
        else {
            /// If pid allocation is sucessful:
            /// Indicate in the in_use map the pid is in use
            in_use[pid] = 1;
            printf("allocated %d\n", pid);

            /// Sleep for a random period of time
            sleep( (int)(random() % SLEEP) );

            /// Release the pid
            release_pid( pid ); 
            in_use[pid] = 0;
            printf("released %d\n", pid);
        }
    }
}

/**
 * Main function. Initializes data structures, creates the threads and has them
 * execute allocator(). Concludes by joining the threads.
 *
 * @return 0 Indicates normal termination of main.
 */
int main(void)
{
    /// Declare variables
    int i;
    pthread_t tids[NUM_THREADS];
    
    /// Initialize in_use array
    for (i = 0; i <= PID_MAX; i++) {
        in_use[i] = 0;
    }

    /// Allocate the pid map
    if (allocate_map() == -1)
        return -1;
    
    /// Seed random generator 
    srandom( (unsigned)time( NULL ) );

    /// Create the threads
    for (i = 0; i < NUM_THREADS; i++)
        pthread_create( &tids[i], NULL, allocator, NULL);

    /// Join the threads
    for (i = 0; i < NUM_THREADS; i++)
        pthread_join( tids[i], NULL ); 

    /// Test is finished

    return 0;
}
