#include <stdio.h>
#include <unistd.h>

int main() {
	int pipefd1[2], pipefd2[2];
	int returnstatus1, returnstatus2;
	int pid;
	char pipe1message[20] = "Hi";
	char pipe2message[20] = "Hello";
	char readmessage[20];

	returnstatus1 = pipe(pipefd1);


	if (returnstatus1 == -1) {
		printf("unable to create pipe 1 \n");
		return 1;
	}

	returnstatus2 = pipe(pipefd2);

	if(returnstatus2 == -1){
		printf("unable to create pipe 2\n");
		return 1;
	}

	pid = fork();

	if (pid != 0) {
		close(pipefd1[0]);
		close(pipefd2[1]);
		printf("writing to pipe 1, Message is %s\n", pipe1message);
		write(pipefd1[1], pipe1message, sizeof(pipe1message));
		read(pipefd2[0], readmessage, sizeof(readmessage));
		printf(" reading from pipe 2, Message is %s\n", readmessage);
	} else {
		close(pipefd1[1]);
		close(pipefd2[0]);
		read(pipefd1[0], readmessage, sizeof(readmessage));
		printf("reading from pipe 1, Message is %s\n", readmessage);
		printf("writing to pipe 2, Message is %s\n", pipe2message);
		write(pipefd2[1], pipe2message, sizeof(pipe2message));
	}

	return 0;
}

