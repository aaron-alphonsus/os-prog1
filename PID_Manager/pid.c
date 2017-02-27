/**
 * @file pid.c
 * 
 * @brief A solution to the pid manager problem. Contains function definitions
 * to create and initialize the pid array, allocate a pid, and release a pid.
 * 
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

#include "pid.h"

/**
 * Initializes pid map and checks if successful
 * 
 * @return -1 if unsuccessful, 0 if successful
 */
int allocate_map( void ) 
{
    /// Mark all pids unused
    for (int i = 0; i < PID_MAX + 1; i++)
        pid_map[i] = 0;
    
    /// Set last to smallest pid
    last = PID_MIN; 
    /// Check if initializaiton succeeds
    for (int i = PID_MIN; i < PID_MAX + 1; i++)
    {
        if ( pid_map[i] != 0)
            last = -1;                  
    }
    
    return last;
}

/**
 * Finds the next available pid and marks it as in use if one is found
 * 
 * @return Allocated pid if successful, -1 if none available
 */
int allocate_pid(void)
{
    /// Local variables 
    int found;    

    /// Acquire the mutex lock and warn if unable 
    if (pthread_mutex_lock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) );
    
    /// Set found to 0
    found = 0;
    /// Find the next available pid. 
    /// Iterate from last to PID_MAX
    for (int i = last; i < PID_MAX + 1 && found == 0; i++)
    {
        /// If pid available, set last to pid and indicate found    
        if (pid_map[i] == 0)
        {
            found = 1;
            pid_map[i] = 1;
            last = i;
        }
    }
    /// Iterate from PID_MIN to last
    for (int i = PID_MIN; i <= last && found == 0; i++)
    {     
        /// If pid available, set last to pid and indicate found 
        if (pid_map[i] == 0)
        {
            found = 1;
            pid_map[i] = 1;
            last = i;
        }
    }
       
    /// Release and warn if the mutex was not released
    if (pthread_mutex_unlock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) );    
    
    /// Returns pid if available, -1 if none available
    if (found == 0)
        return -1;
    else
        return last;
}

/**
 * Releases a pid making sure that the process is sychronized.
 *
 * @param[in] pid The pid to set to unused
 */
void release_pid(int pid)
{
    /// Acquire the mutex lock and warn if unable 
    if (pthread_mutex_lock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) );

    pid_map[pid] = 0;

    /// Release and warn if the mutex was not released */
    if (pthread_mutex_unlock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) ); 
}
