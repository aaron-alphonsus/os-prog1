/**
 * @file help_student.c
 * 
 * @brief Simulate helping a student. 
 *
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */

#include <stdio.h>
#include "ta.h"

/**
 * Function takes in a time in seconds. Prints the time that the student is 
 * helped with the number of waiting students, and sleeps for the given time.
 *
 * @param[in] sleep_time Number of seconds to sleep for 
 */
void help_student(int sleep_time)
{
    /// Print time that student is helped and number of waiting students
    printf( "Helping a student for %d seconds waiting students = %d\n", 
        sleep_time, waiting_students );
    /// Sleep for given number of seconds
    sleep( sleep_time );
}
