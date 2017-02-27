/**
 * @file ta.h
 * 
 * @brief Header file for sleeping TA. Contains definitions for a number of 
 * constants, as well as function prototypes and variable declarations (includes
 * declarations of the mutex lock and semaphores.)
 *
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */
#include <pthread.h>
#include <semaphore.h>

/// The maximum time (in seconds) to sleep
#define MAX_SLEEP_TIME 5

/// Number of maximum waiting students
#define MAX_WAITING_STUDENTS 3

/// Number of potential students
#define NUM_OF_STUDENTS 5

/// Number of available seats
#define NUM_OF_SEATS 3

/// Mutex lock
pthread_mutex_t mutex_lock;

/// Semaphore declarations
sem_t student_sem;
sem_t ta_sem;

/// The number of waiting students
int waiting_students;

/// Student being served
int student_served;

/// The numeric id of each student
int student_id[NUM_OF_STUDENTS + 1];

/// Student function prototype
void *student_loop(void *param);

/// TA function prototype
void *ta_loop(void *param);
