// Pseudo code for the program:
// 1. Define the FIFO file path.
// 2. Create a named FIFO (if it doesn't already exist) using the mknod() system call.
// 3. Open the FIFO in read-only mode.
// 4. Read data from the FIFO written by another process (Program2).
// 5. Display the received data.
// 6. Close the FIFO file descriptor.
// 7. Delete the FIFO after use to clean up resources.
#include <unistd.h>
#include <stdio.h>

int main() {
	char *fifo_name = "/tmp/myfifo";
	int fd = open(fifo_name, O_RDONLY);
	if (fd == -1) {
		perror("Open failed");
		return 1;
	}

	char buffer[100];
	int bytesRead = read(fd, buffer, sizeof(buffer));
	if (bytesRead > 0) {
		buffer[bytesRead] = '\0';
		printf("Reader Received: %s\n", buffer);
	}
	// printf("%ld",sizeof(buffer));
	// printf("Reader recived: %s\n", buffer);

	close(fd);
	unlink(fifo_name); // Deleting the fifo
	return 0;
}

