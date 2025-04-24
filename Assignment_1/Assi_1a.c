// 1. Include necessary header files for system calls and standard I/O.
// 2. Define the main function.
// 3. Declare variables for process IDs and counters for child and grandchild processes.
// 4. Call fork() to create a child process.
//    a. If fork() fails, print an error message and exit with status 1.
//    b. If fork() returns 0 (child process):
//       i. Increment the child process counter.
//       ii. Print the PID and PPID of the child process.
//       iii. Call fork() again to create a grandchild process.
//           - If fork() fails, print an error message and exit with status 1.
//           - If fork() returns 0 (grandchild process):
//             * Increment the grandchild process counter.
//             * Print the PID, PPID, and roll number.
//             * Exit with status 0.
//           - Wait for the grandchild process to complete.
//           - Exit the child process with status 0.
//    c. If fork() returns a positive value (parent process):
//       i. Print the PID of the parent process.
//       ii. Wait for the child process to complete.
//       iii. Print the total number of child and grandchild processes created.
// 5. Return 0 to indicate successful execution.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  // Include this for wait()

int main() {
    pid_t pid, gcid;
    int child_count = 1, grandchild_count = 1;

    pid = fork(); 
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) { // Child process
        child_count++;
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        
        gcid = fork();
        if (gcid < 0) {
            perror("Fork failed");
            exit(1);
        }
        
        if (gcid == 0) { // Grandchild process
            grandchild_count++;
            printf("Grandchild Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            printf("Roll Number: CSM24004\n");
            exit(0);
        }
        
        wait(NULL); // Ensure grandchild completes
        exit(0);
    } 
    else { // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        wait(NULL); // Ensure child completes
        printf("Total Child Processes Created: %d\n", child_count);
        printf("Total Grandchild Processes Created: %d\n", grandchild_count);
    }
    return 0;
}