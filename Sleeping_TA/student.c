/**
 * General structure of a student.
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop( void *param )
{
    /* variables */
    int student_id = *(int *)param; 
    int times_through_loop = 0;    

    srandom( (unsigned)time( NULL ) );

    while (times_through_loop < 5) {

        /* acquire the mutex lock */
        if (pthread_mutex_lock( &mutex_lock ) != 0)
            printf( "StudentA %s\n", strerror( errno ) );

        /* is there a seat available */
        if (waiting_students < MAX_WAITING_STUDENTS) {
            
            waiting_students++;
            
            printf( "\t\tStudent %d takes a seat waiting = %d\n", student_id, 
                waiting_students );

            if (pthread_mutex_unlock( &mutex_lock ) != 0)
                printf( "StudentB %s\n", strerror( errno ) );

            if (sem_post( &student_sem ) != 0)
                printf( "StudentC %s\n", strerror( errno ) );
            
            if (sem_wait( &ta_sem ) != 0)
                printf( "StudentD %s\n", strerror( errno ) );

            printf("Student %d receiving help\n", student_id );

        } 
        else {
            printf("\t\t\tStudent %d will try later\n", student_id);
            pthread_mutex_unlock(&mutex_lock);
            hang_out( student_id, rand() % MAX_SLEEP_TIME);
        }
        times_through_loop++;
    }
}
