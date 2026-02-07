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

    // TODO: Create pipe using pipe(pipefd)

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // TODO: Fork the process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // --- Child process ---
        
        // TODO: Close the write end (child only reads)
        close(pipefd[1]);

        // TODO: Read from pipe into buffer
        int bitRead = fread(buffer, sizeof(buffer),sizeof(buffer), pipefd[0]);
        
        // TODO: Print the received message
        if (bitRead > 0) {
            buffer[bitRead] = '\0'; // null terminating buffer stream
            printf("Child received: %s\n", buffer);
        }

        // TODO: Close read end
        close(pipefd[0]);
        exit(EXIT_SUCCESS);

    } else {
        // --- Parent process ---
        
        // TODO: Close the read end (parent only writes)
        close(pipefd[0]);

        // TODO: Write message to pipe
        write(pipefd[1], message, strlen(message));

        // TODO: Close write end
        close(pipefd[1]);

        // TODO: Wait for child to finish
        wait(NULL);
    }

    return 0;
}