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
   if (  )
      printf("%s\n",strerror(errno));

   if (  )
      printf("error init students_sem\n"); 
	
   if (  )
      printf("error init ta\n");

   for (i = 0; i < NUM_OF_STUDENTS; i++)
      student_id[i] = i;
}

void create_students()
{

   for (i = 0; i < NUM_OF_STUDENTS; i++) {

   }
}

void create_ta()
{

}

int main(void)
{
int i;

   init();
   create_ta();
   create_students();

   for (i = 0; i < NUM_OF_STUDENTS; i++)

   /* when all students have finished, we will cancel the TA thread */	
   if (pthread_cancel(ta) != 0)
      printf("%s\n",strerror(errno));

   return 0;
}

