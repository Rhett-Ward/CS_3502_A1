#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	int pipefd[2];
	pid_t pid;
	char buffer[100];
	char *message = "Hello from parent!";

	// TODO: Create a pipe using pipe(pipefd)
	if(pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}


	pid = fork();
	if(pid < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// TODO: Fork the process

	if(pid == 0) {
		//child process
		close(pipefd[1]);
		//close the write end

		int bitRead = read(pipefd[0], buffer, sizeof(buffer));

		if (bitRead > 0) {
			buffer[bitRead] = '\0';
			printf("Child received: %s\n", buffer);
		}
		//read from pipe into buffer
		//print the recieved message

		close(pipefd[0]);
		exit(EXIT_SUCCESS);
		//close the read end
	} else {
		//parent process

		close(pipefd[0]);
		//close the read end

		write(pipefd[1], message, strlen(message));
		// write message to pipe

		close(pipefd[1]);
		// close write end

		wait(NULL);
		// wait for child to finish
	}

	return(0);
}
