/**
 * @file hangout.c
 * 
 * @brief Simulate a student hanging out.  
 *
 * @authors Dr. Christer Karlsson, Aaron Alphonsus
 *
 * @date 27 February 2017
 */
#include <stdio.h>

/**
 * Function takes in a studentid and time in seconds. Prints the student id with
 * the time it is hanging out and sleeps for that time.
 *
 * @param[in] lnumber ID of the student
 * @param[in] sleep_time Number of seconds to sleep for 
 */
void hang_out(int lnumber, int sleep_time) 
{
    /// Prints the id of the student and time that it hangs out
    printf( "\tStudent %d hanging out for %d seconds\n", lnumber, sleep_time );
    /// Sleep for given number of seconds
    sleep( sleep_time );
}
