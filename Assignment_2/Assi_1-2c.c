/*
* Assignment 2(c)
 * 1. Include necessary headers for input/output and pthread library.
 * 2. Define a thread function `print_hello` that prints "HELLO WORLD" and exits using pthread_exit().
 * 3. In the main function:
 *    a. Declare a thread identifier of type `pthread_t`.
 *    b. Use `pthread_create()` to create a new thread that runs the `print_hello` function.
 *       - Check for errors in thread creation and handle them using `perror()` and `exit()`.
 *    c. Use `pthread_join()` to wait for the created thread to finish execution.
 *    d. Print a message indicating the thread has completed.
 * 4. Return 0 to indicate successful program execution.
 *
 * Purpose of System Calls:
 * - `pthread_create()`: Used to create a new thread at the user level.
 * - `pthread_exit()`: Used to terminate the thread explicitly.
 * - `pthread_join()`: Used to wait for the thread to complete before proceeding.
 */
/*
 * This program creates a user-level thread to print "HELLO WORLD".
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function to print message
void* print_hello(void* arg) {
    printf("HELLO WORLD\n");
    pthread_exit(NULL); 
}
int main() 
{
    pthread_t thread_id;
    // Create a thread
    if (pthread_create(&thread_id, NULL, print_hello, NULL) != 0) {
        perror("pthread_create");

        exit(1);
    }

    // Wait for the thread to finish
    pthread_join(thread_id, NULL);
    printf("Thread completed\n");

    return 0;
}
