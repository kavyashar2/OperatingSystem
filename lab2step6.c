// Name: Kavya Sharma
// Date: 10/2/2024
// Title: Lab 2 Step 6
// Description: Rewritten program from Step 1 with two threads instead of two processes.

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void* onethread(void *i);
void* twothread(void *i);

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	int *i = malloc(sizeof(*i));
	*i = n;
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, onethread, i);
	pthread_create(&thread2, NULL, twothread, i);
	pthread_join(thread1, NULL); // Wait for thread1 to execute
	pthread_join(thread2, NULL); // Wait for thread2 to execute
	return 0;
}

void* onethread(void *i) {
	int j = *((int *) i);
	for(int k = 0; k < 100; k++) {
		printf("\t \t \t Thread 1 %d \n", k);
		usleep(j);
	}
	return 0;
}

void* twothread(void *i) {
	int j = *((int *) i);
	for(int k = 0; k < 100; k++) {
 		printf("Thread 2 %d \n", k);
		usleep(j);
	}
	return 0;
}