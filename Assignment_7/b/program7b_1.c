/*
 * 1. Include necessary headers for shared memory and semaphore operations.
 * 2. Define a function to signal (increment) the semaphore.
 * 3. In the main function:
 *    a. Generate a unique key for shared memory and semaphore.
 *    b. Create a shared memory segment and a semaphore using the key.
 *    c. Attach the shared memory segment to the process's address space.
 *    d. Write a string (e.g., "Hello from Shared Memory!") to the shared memory.
 *    e. Initialize the semaphore to 0 to indicate it's locked.
 *    f. Print a message indicating data has been written to shared memory.
 *    g. Signal the semaphore to notify the other process (prog2) that data is ready.
 *    h. Detach the shared memory segment from the process's address space.
 * 4. Exit the program.

 * Summary:
 * prog1.c writes a string to shared memory and uses a semaphore to signal prog2.c
 * that the data is ready. It demonstrates inter-process communication using shared
 * memory and semaphores.
 */
// Assignment 7b - program1
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

void semaphore_signal(int semid) {
    struct sembuf sb = {0, 1, 0}; // Increment semaphore
    semop(semid, &sb, 1);
}

int main() {
    key_t key = 5678;
    int shmid = shmget(key, 100, 0666 | IPC_CREAT);
    int semid = semget(key, 1, 0666 | IPC_CREAT);

    char *str = (char *)shmat(shmid, NULL, 0);
    sprintf(str, "Hello from Shared Memory!");

    semctl(semid, 0, SETVAL, 0); // Initialize semaphore to 0

    printf("prog1: Data written to shared memory.\n");

    semaphore_signal(semid); // Signal prog2 to read
    shmdt(str); // Detach shared memory

    return 0;
}

