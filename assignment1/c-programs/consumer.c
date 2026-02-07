#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

volatile sig_atomic_t shutdown_flag = 0;
int line_count = 0;
int char_count = 0;


void print_stats() {
	fprintf(stderr, "\n--- Stats ---\n");
	fprintf(stderr, "Lines processed: %d\n", line_count);
	fprintf(stderr, "Total characters: %d\n", char_count);
}

void handle_sigint(int sig){
	shutdown_flag = 1;
	print_stats();
	exit(1);
}

void handle_sigusr1(int sig){
	print_stats();
}

int main(int argc, char *argv[]) {
	int max_lines = -1;
	int active = 0;
	int opt;
	
	struct sigaction sa;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	signal(SIGINT, handle_sigint);
	signal(SIGUSR1, handle_sigusr1);

	while (( opt = getopt(argc, argv, "n:v")) != -1) {
		switch(opt) {
			case 'n':
				max_lines = atoi(optarg);
				break;
			case 'v':
				active = 1;
				break;
			default:
				fprintf(stderr, "Usage: %s [-n max] [-v]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	char *line = NULL;
	size_t len = 0;

	while(!shutdown_flag){
		while (getline (&line, &len, stdin) != -1) {
			line_count++;
			char_count += len;
			sleep(1);
			if(active) {
				printf("Line %d: %s", line_count, line);
			}
			if (max_lines > 0 && line_count >- max_lines) {
				break;
			}
		}
	}
	fprintf(stderr, "Consumer has finished consuming");
	print_stats();
	return 0;
}

