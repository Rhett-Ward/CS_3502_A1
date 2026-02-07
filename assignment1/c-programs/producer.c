#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

volatile sig_atomic_t shutdown_flag = 0;

void handle_sigint(int sig) {
	shutdown_flag = 1;
}

int main(int argc, char *argv[]){
	char *filename = NULL;
	int buffer_size = 4096;

	struct sigaction sa;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	signal(SIGINT, handle_sigint);

	while (!shutdown_flag){
		int opt;
		while ((opt = getopt(argc, argv, "f:b:")) != -1) {
			switch(opt) {
				case 'f':
					filename = optarg;
					break;
				case 'b':
					buffer_size = atoi(optarg);
					break;
				default:
					fprintf(stderr, "Usage: %s [-f file] [-b size]\n", argv[0]);
					exit(1);
			}
		}

		char buff[buffer_size];

		FILE *input;
		if (filename != NULL) {
			input = fopen(filename,"r");
		} else {
			input=stdin;
		}

		int bitRead;
		while ((bitRead = fread(buff, 1, sizeof(buff), input)) > 0) {
			fwrite(buff, 1, bitRead, stdout);
			fflush(stdout);
		}

		fprintf(stderr, "\n producer is experiencing a graceful shutdown\n");
		if(filename) fclose(input);
		return 0;
	}
}

