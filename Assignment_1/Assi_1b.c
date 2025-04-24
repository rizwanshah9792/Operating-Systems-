// Function to print logged-in users
// - Open utmp file
// - Loop through entries
// - If entry is a user process, print user details
// - Close utmp file

// Main function
// - Declare process IDs
// - Fork a child process
//   - If fork fails, print error and exit
//   - If in child process:
//     - Print child process details
//     - Fork a grandchild process
//       - If fork fails, print error and exit
//       - If in grandchild process:
//         - Print grandchild process details
//         - Call function to print logged-in users
//         - Exit grandchild process
//     - Wait for grandchild to finish
//     - Exit child process
//   - If in parent process:
//     - Print parent process details
//     - Wait for child to finish
//     - Print message indicating child process finished

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <utmp.h>

void print_logged_in_users() {
    struct utmp *entry;
    setutent();  // Open /var/run/utmp
    while ((entry = getutent()) != NULL) {
        if (entry->ut_type == USER_PROCESS) {  // Only print active user logins
            printf("User: %s, Terminal: %s, Host: %s\n", entry->ut_user, entry->ut_line, entry->ut_host);
        }
    }
    endutent();  // Close file
}

int main() {
    pid_t pid, gcid;

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());

        gcid = fork();
        if (gcid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (gcid == 0) {  // Grandchild process
            printf("Grandchild Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            print_logged_in_users();
            exit(0);
        }

        wait(NULL);  // Child waits for grandchild
        exit(0);
    } 
    else {  // Parent process
        printf("Parent Process: PID = %d\n", getpid());
       wait(NULL);  // Parent waits for child
        printf("Parent: Child process finished execution.\n");
    }

    return 0;
}