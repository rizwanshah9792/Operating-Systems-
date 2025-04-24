/*
 * 1. Include necessary headers for file operations, process handling, and time measurement.
 * 2. Define the main function.
 * 3. Declare variables to store start and end times using `struct timeval`.
 * 4. Open a file named "process_time.txt" in write mode to store the process times.
 * 5. Record the submission time using `gettimeofday()` and store it in the `start` variable.
 * 6. Create a child process using `fork()`.
 * 7. In the child process:
 *    a. Print a message indicating the child process is running.
 *    b. Simulate some execution using `sleep()`.
 *    c. Exit the child process.
 * 8. In the parent process:
 *    a. Wait for the child process to finish using `wait()`.
 *    b. Record the finish time using `gettimeofday()` and store it in the `end` variable.
 *    c. Write the submission and finish times to the file in seconds and microseconds.
 *    d. Close the file.
 *    e. Print a message indicating the times have been recorded.
 * 9. Return 0 to indicate successful execution.
 *
 * Summary:
 * The program creates a child process and measures its submission and finish times using the `gettimeofday()` system call. These times are written to a file named "process_time.txt". The `fork()` system call is used to create the child process, and `wait()` ensures the parent waits for the child to complete. The program demonstrates basic process handling and time measurement in C.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

int main() {
    struct timeval start, end;
    FILE *file = fopen("process_time.txt", "w");  // Open file to store times
    
    gettimeofday(&start, NULL);  // Record submission time
    pid_t pid = fork(); // Create child process

    if (pid == 0) { // Child process
        printf("Child process is running...\n");
        sleep(3); // Simulate execution
        exit(0);
    } else { // Parent process
        wait(NULL); // Wait for child to finish
        gettimeofday(&end, NULL);  // Record finish time

        fprintf(file, "Submission Time: %ld.%06ld seconds\n", start.tv_sec, start.tv_usec);
        fprintf(file, "Finish Time: %ld.%06ld seconds\n", end.tv_sec, end.tv_usec);
        fclose(file);
        
        printf("Process times recorded in 'process_time.txt'\n");
    }
    return 0;
}

