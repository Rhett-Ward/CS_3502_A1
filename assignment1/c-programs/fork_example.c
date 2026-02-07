#include <stdio.h>
#include <unistd.h>

pid_t pid = fork();

if (pid == -1) {
	//Error
	perror("fork failed");
} else if (pid == 0) {
	//Child process
	printf("I am the child. My PID is %d\n", getpid());
} else {
	//Parent process
	printf("I am the parent. Child's PID is %d\n", pid);
}

