/**
 * A solution to the pid manager problem. 
 *
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

#include "pid.h"

// Creates and initializes pid map. Returns 1 if unsuccessful, 0 if successful.
// 0 indicates process id available. 1 indicates process id in use.
int allocate_map( void ) 
{
    for (int i = 0; i < PID_MAX + 1; i++)
        pid_map[i] = 0;
    
    last = PID_MIN; 
    for (int i = PID_MIN; i < PID_MAX + 1; i++)
    {
        if ( pid_map[i] != 0)
            last = -1;                  
    }

    return last;
}

// Allocates a pid
int allocate_pid(void)
{
    /* local variables */
    int found;    

    /* acquire the mutex lock and warn if unable */
    if (pthread_mutex_lock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) );

    found = 0;
    /* find the next available pid */
    for (int i = last; i < PID_MAX + 1 && found == 0; i++)
    {    
        if (pid_map[i] == 0)
        {
            found = 1;
            pid_map[i] = 1;
            last = i;
        }
    }
    for (int i = PID_MIN; i <= last && found == 0; i++)
    {    
        if (pid_map[i] == 0)
        {
            found = 1;
            pid_map[i] = 1;
            last = i;
        }
    }
       
    /* release and warn if the mutex was not released */
    if (pthread_mutex_unlock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) );    
    
    if (found == 0)
        return -1;
    else
        return last;
}

// Releases a pid
void release_pid(int pid)
{
    /* acquire the mutex lock and warn if unable */
    if (pthread_mutex_lock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) );

    pid_map[pid] = 0;

    /* release and warn if the mutex was not released */
    if (pthread_mutex_unlock( &mutex ) != 0)
        printf( "%s\n", strerror( errno ) ); 
}
