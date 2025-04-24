/*
 * 1. Include necessary headers for shared memory operations and standard I/O.
 * 2. Define a unique key for shared memory identification.
 * 3. Access an existing shared memory segment using shmget with the defined key.
 *    - If shmget fails, print an error message and exit.
 * 4. Attach the shared memory segment to the process's address space using shmat.
 *    - If shmat fails, print an error message and exit.
 * 5. Read the integer value from the shared memory and print it.
 * 6. Detach the shared memory segment from the process using shmdt.
 * 7. Remove the shared memory segment using shmctl with IPC_RMID command.
 * 8. Exit the program.
 */

/*
 * Summary:
 * This program (program2.c) demonstrates shared memory usage by reading data written by another process (program1.c).
 * It accesses an existing shared memory segment, reads the data, and then cleans up by detaching and removing the shared memory.
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), 0666); // Access existing shared memory
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    int *shared_data = (int *)shmat(shmid, NULL, 0); // Attach memory
    if (shared_data == (int *)-1) {
        perror("shmat failed");
        return 1;
    }

    printf("Process 2 read from shared memory: %d\n", *shared_data);

    shmdt(shared_data); // Detach memory
    shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
    return 0;
}

