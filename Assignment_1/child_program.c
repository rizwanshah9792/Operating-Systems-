// Pseudo code for child program:
// 1. Include necessary headers.
// 2. Define the main function with arguments for argc and argv.
// 3. Print the program name using argv[0].
// 4. Print the PID of the child process using getpid().
// 5. Exit the program.

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Child Program Name: %s\n", argv[0]);
    printf("Child Process is running with PID: %d\n", getpid());

    return 0; 
}