/*
1. Include necessary headers for shared memory operations and standard I/O.
2. Define a unique key for shared memory creation.
3. Create a shared memory segment using shmget() with the defined key and required size.
    - If creation fails, print an error message and exit.
4. Attach the shared memory segment to the process's address space using shmat().
    - If attachment fails, print an error message and exit.
5. Write the process ID of the current process into the shared memory.
6. Print a message indicating that the process ID has been written to shared memory.
7. Detach the shared memory segment from the process's address space using shmdt().
8. Exit the program.

Summary:
This program (program1.c) demonstrates the creation and usage of shared memory in a Linux environment. It writes the process ID of the current process into a shared memory segment, which can be read by another program (program2.c). The shared memory segment is properly detached after use.
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key = 1234;  // Unique key for shared memory
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT); // Create shared memory
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    int *shared_data = (int *)shmat(shmid, NULL, 0); // Attach memory
    if (shared_data == (int *)-1) {
        perror("shmat failed");
        return 1;
    }

    *shared_data = getpid(); // Write Process ID to shared memory
    printf("Process 1 (PID: %d) wrote to shared memory.\n", *shared_data);

    shmdt(shared_data); // Detach memory
    return 0;
}

