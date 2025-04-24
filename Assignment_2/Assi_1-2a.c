/*
* Assignment 2(a)
 * 1. Include necessary headers for input/output, process control, and signal handling.
 * 2. Define a signal handler function:
 *    a. Print a message indicating SIGINT was received.
 *    b. Use fork() to create a child process.
 *    c. In the child process:
 *       i. Print the child process ID and its parent process ID.
 *       ii. Exit the child process to prevent it from continuing the parent's execution flow.
 *    d. In the parent process:
 *       i. Use wait() to ensure the child process completes execution to avoid zombie processes.
 * 3. In the main function:
 *    a. Register the signal handler for SIGINT using signal().
 *    b. Use an infinite loop with pause() to keep the process alive and waiting for signals.
 * 4. Compile and run the program. Press Ctrl+C to test the signal handling and process creation.
 */
/*
 * This program demonstrates handling SIGINT to create a child process using fork().
 * When Ctrl+c is pressed, the parent and child processes print their PIDs and PPIDs.
 */

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int num) {
        printf("Ctrl + C pressed\n");
        pid_t pid;
        pid = fork();
        if (pid < 0) {
                perror("Fork Failed");
                exit(1);
        }
        if (pid == 0) {
                printf("Child Process Created \nPID = %d, Parent PID = %d\n", getpid(), getppid());
		exit(0); // Terminates child immediately
        }

        else {
                wait(NULL); //Ensure child completes to prevent to become zombiee
	}
}

int main() {
        signal(SIGINT, signal_handler);

        // Keep process alive to handle signal
	while(1){
		pause(); // No busy loop
	}
        return 0;
}
