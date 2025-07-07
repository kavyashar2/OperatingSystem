// Name: Kavya Sharma
// Date: 10/9/2024
// Title: Lab3 – Part 5
// Description: C program that implements the producer-consumer message communication using pipes.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int fds[2];
	pipe(fds);  
	char buff[60]; 
	int count;

	//child 1
	if (fork() == 0) {
		printf("Producer started\n");
		close(fds[0]);  // Close read end of the pipe (producer doesn't need it)
		char input[60];

		while (1) {
			printf("Enter a message (type 'exit' to stop): ");
			scanf("%s", input);
			
			write(fds[1], input, strlen(input) + 1);

			if (strcmp(input, "exit") == 0) {
				break;
			}
		}
		close(fds[1]);
		exit(0);
	}

	//child 2
	else if (fork() == 0) {
		close(fds[1]);  

		while (1) {
			count = read(fds[0], buff, sizeof(buff));

			if (strcmp(buff, "exit") == 0) {
				break;
			}

			printf("Consumer received: %s\n", buff);
		}
		close(fds[0]);
		exit(0);
	}

	//parent process waits for both children to finish
	else {
		close(fds[0]);  
		close(fds[1]);  
		wait(0); 
		wait(0);  
	}
	return 0;
}
