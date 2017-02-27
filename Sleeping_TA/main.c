#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"

pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
    waiting_students = 0;   
    student_served = 0;

    if (pthread_mutex_init( &mutex_lock, NULL ) != 0)
        printf( "%s\n",strerror( errno ) );

    if (sem_init( &student_sem, 0, 0 ) != 0)
        printf( "error init students_sem\n" ); 

    if (sem_init( &ta, 0, 0 ) != 0)
        printf( "error init ta_sem\n" );

    for (int i = 0; i < NUM_OF_STUDENTS; i++)
        student_id[i] = i;
}

void create_students()
{
    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        pthread_create( &students[i], NULL, student_loop, 
            (void *)&student_id[i] );
    }
}

void create_ta()
{
    pthread_create( &ta, NULL, ta_loop, NULL);
}

int main( void )
{
    int i;

    init();
    create_ta();
    create_students();

    for (i = 0; i < NUM_OF_STUDENTS; i++)
    {
        pthread_join( students[i], NULL );
    }

    /* when all students have finished, we will cancel the TA thread */	
    if (pthread_cancel( ta ) != 0)
        printf( "%s\n", strerror( errno ) );

    return 0;
}
