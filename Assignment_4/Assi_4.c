// This program demonstrates file locking using `fcntl()` in a multi-process environment.
// It locks a file, reads its contents, holds the lock for 10 seconds, and then releases the lock.
// 1. Include necessary headers for file operations, locking, and process control.
// 2. Define a function `lock_file` to set or release a file lock using `fcntl()`.
//    - Initialize a `struct flock` with appropriate lock type, offset, and length.
//    - Use `fcntl()` with `F_SETLKW` to set or release the lock, handling errors.
// 3. In the `main` function:
//    - Check if the filename is provided as a command-line argument.
//    - Open the file in read-write mode using `fopen()`.
//    - Handle errors if the file cannot be opened.
//    - Print the process ID and attempt to lock the file using `lock_file`.
//    - Read the file contents using `read()` and print them to the console.
//    - Handle errors during reading and release the lock if necessary.
//    - Hold the lock for 10 seconds to simulate exclusive access.
//    - Release the lock using `lock_file` and close the file.
//    - Exit the program.
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void lock_file(int fd, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;    // F_WRLCK (write lock) or F_UNLCK (unlock)
    lock.l_whence = SEEK_SET;   // Start from beginning of file
    lock.l_start = 0;           // Offset 0
    lock.l_len = 0;             // Lock entire file (0 means to end)
    
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error setting lock");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    FILE* fptr;
    char content[255];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }


    fptr = fopen(argv[1], "r+"); // "r+" for locking
    if (fptr == NULL) {
        printf("File open Unsuccessful\n");
        return 1;
    }

    printf("Process %d: Attempting to lock file...\n", getpid());
    lock_file(fileno(fptr), F_WRLCK);
    printf("Process %d: File locked. Reading contents...\n", getpid());

    int fd = fileno(fptr);
    ssize_t bytes_read;
    while ((bytes_read = read(fd, content, sizeof(content) - 1)) > 0) {
        content[bytes_read] = '\0';
        printf("%s", content);
    }
    if (bytes_read == -1) {
        perror("Error reading file");
        lock_file(fd, F_UNLCK);
        fclose(fptr);
        return 1;
    }

    printf("\nProcess %d: Holding lock for 10 seconds...\n", getpid());
    sleep(10);

    printf("Process %d: Unlocking file...\n", getpid());
    lock_file(fd, F_UNLCK);

    fclose(fptr);
    return 0;
}
