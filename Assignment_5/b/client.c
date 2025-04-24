// Include necessary headers
// Define constants and message structure

// Main function
// 1. Generate a unique key using ftok() to identify the message queue
// 2. Connect to the message queue using msgget()
// 3. Prompt the user to enter a message
// 4. Remove the newline character from the input
// 5. Set the message type to 1 (for server)
// 6. Send the message to the server using msgsnd()
// 7. Handle errors if message sending fails
// 8. Wait for a reply from the server (type 2) using msgrcv()
// 9. Handle errors if message receiving fails
// 10. Print the server's reply
// 11. Exit the program

// Summary:
// This client program demonstrates inter-process communication (IPC) using System V Message Queues. 
// It connects to a message queue, sends a message to the server, and waits for a reply. The message 
// queue ID is generated using ftok() and connected using msgget(). Messages are sent and received 
// using msgsnd() and msgrcv(), respectively.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MAX_SIZE 100

// Message structure
struct msgbuf {
	long mtype;
	char mtext[MAX_SIZE];
};

int main() {
	key_t key;
	int msqid;
	struct msgbuf message;

	// Generate the same key as server
	key = ftok("progfile", 65);

	// Connect to the message queue
	msqid = msgget(key, 0666);

	// Get user input
	printf("Client: enter a message: ");
	fgets(message.mtext, MAX_SIZE, stdin);
	message.mtext[strcspn(message.mtext, "\n")] = 0; // Remove newlind
	message.mtype = 1; // Type 1 fro server
	
	// Send message
	if (msgsnd(msqid, &message, strlen(message.mtext) + 1, 0) == -1) {
		perror("msgsnd failed");
		exit(1);
	}

	// Recieve reply (type 2 from server)
	if (msgrcv(msqid, &message, MAX_SIZE, 2, 0) == -1) {
		perror("msgrcv failed");
		exit(1);
	}

	printf("Client: Server replied: %s\n", message.mtext);
	return 0;
}
