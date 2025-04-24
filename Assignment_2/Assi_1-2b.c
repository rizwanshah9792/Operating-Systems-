/*
 * Assignment 2(b)
 * 1. Include necessary headers for input/output, signal handling, and process control.
 * 2. Define a signal handler function to display the received signal ID.
 * 3. In the main function:
 *    a. Declare variables for Process ID (pid) and Signal ID (sig).
 *    b. Register the signal handler for all possible signals (1 to 31).
 *    c. Prompt the user to enter the Process ID and Signal ID.
 *    d. Validate the input to ensure the PID and Signal ID are valid.
 *    e. Use the kill() system call to send the specified signal to the given process.
 *    f. Handle errors if the kill() system call fails.
 * 4. Display appropriate messages for successful or failed signal delivery.
 * 5. Exit the program.
 */
/*
 * This program takes a Process ID (PID) and a Signal ID as input and sends the signal to the specified process.
 * The purpose is to demonstrate the use of the kill() system call.
 * The receiving process (modified Assignment 2(a)) should handle the signal and display the received signal ID.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function to display received signal ID
void signal_handler(int signum) {
    printf("Received Signal: %d\n", signum);
}

int main() {
    pid_t pid; 
    int sig;  

    // All possible signals
    for (int i = 1; i < 32; i++) {
        signal(i, signal_handler);
    }
    printf("Enter Process ID: ");
    scanf("%d", &pid);
    printf("Enter Signal ID: ");
    scanf("%d", &sig);

    // Validate input
    if (pid <= 0 || sig <= 0 || sig > 31) {
        printf("Invalid PID or Signal ID\n");
        return 1;
    }

    // Send signal to process using kill()
    if (kill(pid, sig) == 0) {
        printf("Signal %d sent to process %d successfully.\n", sig, pid);
    } else {
        perror("Failed to send signal");
        return 1;
    }

    return 0;
}

