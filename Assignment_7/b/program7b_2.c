/*
    Pseudo Code:
    1. Include necessary headers for shared memory and semaphore operations.
    2. Define a function `semaphore_wait` to decrement the semaphore value (wait operation).
    3. In the `main` function:
       a. Generate a unique key for shared memory and semaphore.
       b. Access the shared memory segment and semaphore created by prog1.
       c. Wait for prog1 to write data into the shared memory using `semaphore_wait`.
       d. Attach the shared memory segment to the process's address space.
       e. Read and print the data from the shared memory.
       f. Detach the shared memory segment from the process's address space.
       g. Remove the semaphore and shared memory segment using appropriate system calls.
       h. Print a message indicating successful cleanup.
    4. End the program.

    Summary:
    This program (prog2.c) reads data from a shared memory segment written by prog1.c. 
    It uses a semaphore to synchronize access, ensuring prog1 writes data before prog2 reads it. 
    After reading, it cleans up by removing the semaphore and shared memory.
*/
// Assignment 7b - program2
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

void semaphore_wait(int semid) {
    struct sembuf sb = {0, -1, 0}; // Decrement semaphore
    semop(semid, &sb, 1);
}

int main() {
    key_t key = 5678;
    int shmid = shmget(key, 100, 0666);
    int semid = semget(key, 1, 0666);

    semaphore_wait(semid); // Wait for prog1 to write

    char *str = (char *)shmat(shmid, NULL, 0);
    printf("prog2: Data read from shared memory: %s\n", str);
    shmdt(str); // Detach shared memory

    // Remove semaphore and shared memory
    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);
    printf("prog2: Semaphore and shared memory removed.\n");

    return 0;
}

