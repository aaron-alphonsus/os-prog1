/**
 * General structure of the teaching assistant.
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *ta_loop( void *param )
{
    /* seed random generator */
    srandom( (unsigned)time( NULL ) );

    while (1) {
        /* wait for a student to show up */
        if (sem_wait( &student_sem ) != 0)
            printf( "%s\n", strerror( errno ) );

        /* acquire the mutex lock */
        if (pthread_mutex_lock( &mutex_lock ) != 0)
            printf( "%s\n", strerror( errno ) );
        waiting_students--;        

        /* indicate the TA is ready to help a student */
        if (sem_post( &ta_sem ) != 0)
            printf( "%s\n", strerror( errno ) );

        /* release mutex lock */
        if (pthread_mutex_unlock( &mutex_lock ) != 0)
            printf( "%s\n", strerror( errno ) );

        /* helping students random time */
        help_student( rand() % MAX_SLEEP_TIME );
    }
}
