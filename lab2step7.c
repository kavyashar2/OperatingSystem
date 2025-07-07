// Name: Kavya Sharma
// Date: 10/2/2024
// Title: Lab 2 Step 7
// Description: In this program, the parent process spawns a child which runs the ls command. 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	pid_t  pid;
	int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay

	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	if (pid == 0) {
		execlp("/bin/ls", "ls", NULL);
	}
	else {
		wait(NULL);
		printf("Child Complete");
		exit(0);
	}
	return 0;
}