/*
 * 1. Include necessary headers for semaphore and file operations.
 * 2. Define a function `semaphore_wait` to decrement the semaphore value (wait operation).
 * 3. In the `main` function:
 *    a. Generate a unique key for the semaphore using `key_t`.
 *    b. Access the existing semaphore set using `semget`.
 *    c. Wait for the semaphore to be released by program1 using `semaphore_wait`.
 *    d. Open the file "sample.txt" in read mode.
 *    e. Read and print the contents of the file character by character.
 *    f. Close the file after reading.
 *    g. Remove the semaphore using `semctl` to clean up resources.
 *    h. Print a message indicating program2 has completed.
 */

/*
 * Summary:
 * This program (program2.c) ensures synchronization with program1.c using semaphores.
 * It waits for program1 to finish reading the file before it starts reading the same file.
 * After reading, it removes the semaphore to clean up resources.
 */
// Assignment 7a - program2
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

void semaphore_wait(int semid) {
    struct sembuf sb = {0, -1, 0}; // Decrement semaphore by 1
    semop(semid, &sb, 1);
}

int main() {
    key_t key = 1234;
    int semid = semget(key, 1, 0666); // Access existing semaphore

    // Wait until program1 completes
    semaphore_wait(semid);

    FILE *file = fopen("sample.txt", "r");

    char ch;
    printf("Program2 is reading the file after Program1:\n");
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }
    fclose(file);

    // Remove the semaphore after use
    semctl(semid, 0, IPC_RMID);
    printf("\nProgram2 completed and semaphore removed.\n");

    return 0;
}

