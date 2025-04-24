/*
 * 1. Include necessary headers and define constants.
 * 2. Define a structure for the message queue with a type and text field.
 * 3. In the main function:
 *    a. Generate a unique key using ftok().
 *    b. Create a message queue using msgget() with appropriate permissions.
 *    c. Print the message queue ID to stderr for debugging purposes.
 *    d. Enter an infinite loop to handle messages:
 *       i. Receive a message of type 1 from the client using msgrcv().
 *       ii. Print the received message to the console.
 *       iii. Prepare a reply message with type 2 and a predefined response.
 *       iv. Send the reply message back to the client using msgsnd().
 *       v. Break the loop after one message for demonstration purposes.
 *    e. Remove the message queue using msgctl() with IPC_RMID to clean up.
 *    f. Print a message indicating the server is exiting.
 * 4. Return 0 to indicate successful execution.
 *
 * Summary:
 * The server program demonstrates inter-process communication (IPC) using System V Message Queues.
 * It receives a message from a client, processes it, sends a reply, and cleans up the message queue.
 */
// Server Program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 100

// Message structuree
struct msgbuf {
	long mtype; // Message type
	char mtext[MAX_SIZE];
};

int main() {
	key_t key;
	int msqid;
	struct msgbuf message;

	// Generate a unique key
	key = ftok("progfile", 65); // progfile is dummy file, 65 id a random character

	// Create message queue
	msqid = msgget(key, 0666 | IPC_CREAT);

	// Print queue ID to stderr
    	fprintf(stderr, "Message Queue ID: %d\n", msqid);
    	printf("Server: Waiting for messages...\n");

    	while (1) {
       	 	// Receive message of type 1 (from client)
        	if (msgrcv(msqid, &message, MAX_SIZE, 1, 0) == -1) {
            		perror("msgrcv failed");
            		exit(1);
        	}

        	printf("Server: Received: %s\n", message.mtext);

        	// Prepare reply
        	message.mtype = 2; // Type 2 for client
        	strcpy(message.mtext, "Got it!");
        	if (msgsnd(msqid, &message, strlen(message.mtext) + 1, 0) == -1) {
            		perror("msgsnd failed");
           	 	exit(1);
        	}

        	// For demo, break after one message (remove this for continuous run)
        	break;
    	}

	// Remove the message queue
	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("magctl failed");
		exit(1);
	}

	printf("Server: Queue removed. Exiting.\n");
	return 0;

}

