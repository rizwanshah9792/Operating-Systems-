/*
1. Include necessary headers for semaphore operations and file handling.
2. Define a function `semaphore_signal` to increment the semaphore value by 1.
3. In the `main` function:
    a. Generate a unique key for the semaphore using `key_t`.
    b. Create a semaphore set with one semaphore using `semget`.
    c. Initialize the semaphore value to 0 using `semctl`.
    d. Open the file "sample.txt" in read mode.
    e. Read the contents of the file character by character and print them to the console.
    f. Close the file after reading.
    g. Signal the semaphore to indicate that Program1 has completed reading the file.
    h. Print a message indicating that Program1 has completed and signaled Program2.
4. End the program.

Summary:
This program (Program1) reads the contents of a file and uses a semaphore to synchronize with another program (Program2). The semaphore ensures that Program2 can only read the file after Program1 has completed its reading. The semaphore is initialized to 0 and incremented by 1 after Program1 finishes reading, signaling Program2 to proceed.
*/
// Assignment 7a - program1
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

void semaphore_signal(int semid) {
    struct sembuf sb = {0, 1, 0}; // Increment semaphore by 1
    semop(semid, &sb, 1);
}

int main() {
    key_t key = 1234;
    int semid = semget(key, 1, 0666 | IPC_CREAT); // Create semaphore

    // Initialize semaphore to 0 initially
    semctl(semid, 0, SETVAL, 0);

    FILE *file = fopen("sample.txt", "r");
    
    char ch;
    printf("Program1 is reading the file:\n");
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }
    fclose(file);

    // After reading, signal program2
    semaphore_signal(semid);
    printf("\nProgram1 completed. Signaled Program2.\n");

    return 0;
}
