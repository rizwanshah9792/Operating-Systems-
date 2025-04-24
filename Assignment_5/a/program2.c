// Pseudo code for Program2:

/*
1. Include necessary header files for file operations, FIFO handling, and standard I/O.
2. Define the FIFO name (path) as a string constant.
3. Create the FIFO using the mknod() system call with appropriate permissions (read/write for all users).
4. Open the FIFO in write-only mode using the open() system call.
    - If the open() call fails, print an error message and exit the program.
5. Prompt the user to input a message.
6. Read the user input using fgets() and remove the trailing newline character.
7. Write the user input to the FIFO using the write() system call.
8. Print a confirmation message indicating the message has been sent.
9. Close the FIFO file descriptor using the close() system call.
10. Exit the program.
*/
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *fifo_name = "/tmp/myfifo";
    mknod(fifo_name, S_IFIFO | 0666, 0); // Create FIFO

    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    printf("Send your message from here!\nType: ");
    char message[100];

    fgets(message, sizeof(message), stdin);
    //scanf("%s", message);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character
					
    write(fd, message, strlen(message) + 1);
    printf("Writer sent: %s\n", message);

    close(fd);
    return 0;
}
