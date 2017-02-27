/**
 * @file ta.c
 * 
 * @brief General structure of the teaching assistant. 
 *
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

/**
 * This function defines the behavior of the TA. We perform a sem_wait to wait 
 * for a student to show up. When a student shows up, we acquire the mutex, post
 * the TA semaphore, and release the mutex. After this, we make a call to 
 * help_student() to simulate helping a student for a random amount of time.
 * 
 * @param[in] param Void pointer
 */
void *ta_loop( void *param )
{
    /// Seed random generator
    srandom( (unsigned)time( NULL ) );

    while (1) {
        /// Wait for a student to show up
        if (sem_wait( &student_sem ) != 0)
            printf( "%s\n", strerror( errno ) );

        /// Acquire the mutex lock
        if (pthread_mutex_lock( &mutex_lock ) != 0)
            printf( "%s\n", strerror( errno ) );
        waiting_students--; /// Decrement number of waiting students      

        /// Indicate the TA is ready to help a student
        if (sem_post( &ta_sem ) != 0)
            printf( "%s\n", strerror( errno ) );

        /// Release mutex lock
        if (pthread_mutex_unlock( &mutex_lock ) != 0)
            printf( "%s\n", strerror( errno ) );

        /// Help students random time
        help_student( rand() % MAX_SLEEP_TIME );
    }
}
