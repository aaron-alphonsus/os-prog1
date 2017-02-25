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

void *student_loop(void *param)
{
   /* varaibles */

   srandom((unsigned)time(NULL));

   while (times_through_loop < 5) {

      /* acquire the mutex lock */
      if ( )
         printf("StudentA %s\n",strerror(errno));

      /* is there a seat available */
      if ( ) {

         printf("\t\tStudent %d takes a seat waiting = %d\n", , );
			
         if ( )
             printf("StudentB %s\n",strerror(errno));

         if ( )
             printf("StudentC %s\n",strerror(errno));

         if ( )
             printf("StudentD %s\n",strerror(errno));
			
         printf("Student %d receiving help\n", );
			
       } 
       else {
          printf("\t\t\tStudent %d will try later\n", );
          pthread_mutex_unlock(&mutex_lock);
       }
   }
}

