/**
 * test.c
 *
 * Test the implementation of the PID manager.
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS   10
#define SLEEP         5

int in_use[PID_MAX + 1];

/**
 * mutex lock used when accessing data structure
 * to ensure there are no duplicate pid's in use.
 */
pthread_mutex_t test_mutex;

void *allocator(void *param)
{
   int i, pid;

   for (i = 0; i < ITERATIONS; i++) {
      /* sleep for a random period of time */
		sleep((int)(random() % SLEEP));

      /* allocate a pid */

      if (pid == -1)
         printf("No pid available\n");
      else {
         /* indicate in the in_use map the pid is in use */
		
         /* sleep for a random period of time */
         
         /* release the pid */

      }
   }
}

int main(void)
{
   int i;
   pthread_t tids[NUM_THREADS];

   for (i = 0; i <= PID_MAX; i++) {
      in_use[i] = 0;
   }


   /* allocate the pid map */
   if (allocate_map() == -1)
      return -1;

   srandom((unsigned)time(NULL));

   /* create the threads */

   /* join the threads */

   /* test is finished */

   return 0;
}
