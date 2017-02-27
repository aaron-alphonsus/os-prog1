/**
 * @file main.c
 *
 * @brief Main file for sleeping TA. Program execution begins by calling the 
 * init() function which initializes the student_id array, mutex and semaphores.
 * It then creates a TA thread to run ta_loop(), and student threads to run  
 * student_loop(). Program execution in concluded by joining the student threads
 * and canceling the TA thread.
 *
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 * 
 * @date 27 February 2017 
 */

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"

/// Define TA and student threads
pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * This function initializes all relevant variables, data structures and 
 * synchronization objects.
 */
void init()
{
    waiting_students = 0; /// Initialize waiting students to 0   
    student_served = -1; /// Initialize student being served to -1

    /// Initialize mutex
    if (pthread_mutex_init( &mutex_lock, NULL ) != 0)
        printf( "%s\n",strerror( errno ) );
    
    /// Initialize student semaphore
    if (sem_init( &student_sem, 0, 0 ) != 0)
        printf( "error init student_sem\n" ); 
    
    /// Initialize TA semaphore
    if (sem_init( &ta_sem, 0, 0 ) != 0)
        printf( "error init ta_sem\n" );
    
    /// Initialize student id array
    for (int i = 0; i < NUM_OF_STUDENTS; i++)
        student_id[i] = i;
}

/**
 * This function creates a thread for each student to execute student_loop() and 
 * pass in its student id as a parameter. 
 */
void create_students()
{
    /// Loop through number of students creating student threads
    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        pthread_create( &students[i], NULL, student_loop, 
            (void *)&student_id[i] );
    }
}

/**
 * This function creates a TA thread to execute ta_loop()
 */
void create_ta()
{
    /// Create TA thread to run ta_loop()
    pthread_create( &ta, NULL, ta_loop, NULL);
}

/**
 * This is the main function. It makes function calls to initialize variables and 
 * synchronization objects, create the TA thread, and create student threads. It 
 * then joins the student threads, followed by the cancellation of the TA thread.
 *
 * @return 0 Indicates normal termination of main.
 */
int main( void )
{
    /// Declare iterator variable
    int i;

    /// Function call to initialize variables and synchronization objects
    init();
    /// Function call to create TA thread to execute ta_loop()
    create_ta();
    /// Function call to create student threads to execute student_loop()
    create_students();

    /// Join student threads
    for (i = 0; i < NUM_OF_STUDENTS; i++)
    {
        pthread_join( students[i], NULL );
    }

    /// When all students have finished, we will cancel the TA thread	
    if (pthread_cancel( ta ) != 0)
        printf( "%s\n", strerror( errno ) );

    return 0;
}
