/**
 * @file pid.h
 * 
 * @brief Header file for pid manager. Contains declaration of array keeping 
 * track of pids in use, last pid in use, and mutex lock for sychronization.
 * 
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */

#include <pthread.h>

/// Range of possible pids 
#define PID_MIN  	300
#define PID_MAX 	500

/// Mutex lock for accessing pid_map
pthread_mutex_t mutex;

/// Array representing pids in use
int pid_map[PID_MAX+1];

int last; /// Last pid in use
