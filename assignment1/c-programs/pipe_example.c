#include <unistd.h>

int pipefd[2];
pipe(pipefd);

//Pipefd[0] is the read end
//Pipefd[1] is the write end


