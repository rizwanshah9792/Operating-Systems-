// Include necessary header files for signal handling, process creation, and inter-process communication

// Define a signal handler function 'handler' to handle SIGINT signal
// Inside the handler:
// 1. Create a pipe for communication between parent and child processes
// 2. Use fork() to create a child process
// 3. In the child process:
//    a. Close the read end of the pipe
//    b. Write the child's process ID to the pipe
//    c. Take input N (number of Fibonacci terms) from the user
//    d. Write N to the pipe
//    e. Generate the Fibonacci series up to N terms and write each term to the pipe
//    f. Write the signal ID (SIGINT) to the pipe
//    g. Close the write end of the pipe and exit
// 4. In the parent process:
//    a. Close the write end of the pipe
//    b. Read the child's process ID from the pipe and display it
//    c. Read N from the pipe and display the Fibonacci series terms received from the child
//    d. Read the signal ID from the pipe and display it
//    e. Close the read end of the pipe and wait for the child process to terminate

// In the main function:
// 1. Register the signal handler for SIGINT
// 2. Enter an infinite loop to simulate a running program
// 3. Print a message indicating the main program is running and sleep for 1 second
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void handler(int sig) {
	int pipefd[2];
	if(pipe(pipefd) == -1) {
		perror("pipe Failed");
		exit(1);
	}
	pid_t pid = fork();
	if(pid == -1) {
		perror("fork Failed");
		exit(1);
	}
	if(pid == 0) {
		close(pipefd[0]);
		pid_t mypid = getpid();
		write(pipefd[1], &mypid, sizeof(pid_t));

		int N;
		printf("Enter N: ");
		scanf("%d", &N);
		write(pipefd[1], &N, sizeof(int));

		int a = 0, b = 1, c;
		for(int i = 0; i < N; i++) {
			write(pipefd[1], &a, sizeof(int));
			c = a + b;
			a = b;
			b = c;
		}
		write(pipefd[1], &sig, sizeof(int));
		close(pipefd[1]);
		exit(0);
	}
	else {
		close(pipefd[1]);
		pid_t child_pid;
	read(pipefd[0], &child_pid, sizeof(pid_t));
	printf("child PID: %d\n", child_pid);

	int N;
	read(pipefd[0], &N, sizeof(int));
	printf("Fibonacci series up to %d terms: ", N);

	int term;
	for(int i = 0; i<N; i++) {
		read(pipefd[0], &term, sizeof(int));
		printf("%d ", term);
	}
	printf("\n");
	int signal_id;
	read(pipefd[0], &signal_id, sizeof(int));
	printf("Signal ID: %d\n", signal_id);

	close(pipefd[0]);
	wait(NULL);
	}
}

int main() {
	signal(SIGINT, handler);
	while(1) {
		printf("Main program running...\n");
		sleep(1);
	}
	return 0;
}
