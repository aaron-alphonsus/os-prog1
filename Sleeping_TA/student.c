/**
 * @file student.c
 * 
 * @brief General structure of a student. 
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
 * This function simulates student behavior. We first acquire the mutex lock. If 
 * there is an available seat, we increment the number of waiting students, print
 *  the student which takes a seat and the number of students waiting. We then 
 * release the mutex, and use the student and TA semaphores to track the students
 * waiting on the TA and whether the TA is free. If there is no available seat, 
 * we unlock the mutex and call the hangout function so that the student can try
 * again later.
 *
 * @param[in] param Pointer to an int pointer to the student id
 */

void *student_loop( void *param )
{
    /// Declare local variables
    int student_id = *(int *)param; 
    int times_through_loop = 0;    

    /// Seed random generator
    srandom( (unsigned)time( NULL ) );

    /// Student leaves after going for help 5 times
    while (times_through_loop < 5) {

        /// Acquire the mutex lock
        if (pthread_mutex_lock( &mutex_lock ) != 0)
            printf( "StudentA %s\n", strerror( errno ) );

        /// Check for available seat, else hangout.
        if (waiting_students < MAX_WAITING_STUDENTS) {
           
            /// Increment number of waiting students 
            waiting_students++;
            
            /// Print which student takes a seat and number waiting. 
            printf( "\t\tStudent %d takes a seat waiting = %d\n", student_id, 
                waiting_students );
            
            /// Release mutex lock  
            if (pthread_mutex_unlock( &mutex_lock ) != 0)
                printf( "StudentB %s\n", strerror( errno ) );

            /// Signals students waiting for TA  
            if (sem_post( &student_sem ) != 0)
                printf( "StudentC %s\n", strerror( errno ) );
            
            /// Wait until TA isn't helping another student 
            if (sem_wait( &ta_sem ) != 0)
                printf( "StudentD %s\n", strerror( errno ) );
            
            /// Print which student is receiving help
            printf("Student %d receiving help\n", student_id );
        } 
        
        else {
            /// No available seat
            
            /// Print student will try later
            printf("\t\t\tStudent %d will try later\n", student_id);
            /// Release mutex lock
            pthread_mutex_unlock( &mutex_lock );
            /// Function call simulating student hanging out
            hang_out( student_id, rand() % MAX_SLEEP_TIME);
        }
        /// Increment loop counter
        times_through_loop++;
    }
}
