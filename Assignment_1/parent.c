// Pseudo code for the parent program:
// 1. Create a child process using fork().
// 2. In the child process:
//    a. Print the PID and parent PID.
//    b. Prepare arguments for execv().
//    c. Overlay the child process with a new program using execv().
//    d. Handle errors if execv() fails.
// 3. In the parent process:
//    a. Wait for the child process to finish using wait().
//    b. Check if the child exited normally using WIFEXITED.
//    c. Print the child's exit status or an error message.
//    d. Print the parent's PID.

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);

    } else if (pid == 0) {
        // CP
        printf("Child Process before execv(): PID = %d, Parent PID = %d\n", getpid(), getppid());

        // Prepare arguments for execv()
        char *args[] = {"./child_program", NULL};

        //Overlay child process with child_program using execv()
        if (execv(args[0], args) < 0) {
            perror("execv failed");
            exit(1);
        }
    } else {
        //Parent process
        //wait for child process to finish
        if (wait(&status) < 0) {
            perror("wait failed");
            exit(1);
        }

        // Check if child exited normally
        if (WIFEXITED(status)) {
            printf("Parent Process: Child exited with status = %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent Process: Child did not exit normally\n");
        }

        printf("Parent Process: PID = %d\n", getpid());
    }

    return 0;
}