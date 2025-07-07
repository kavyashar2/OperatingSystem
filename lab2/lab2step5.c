// Name: Kavya Sharma
// Date: 10/2/2024
// Title: Lab 2 Step 5
// Description: This program creates exactly seven processes, one of which is the original parent process, while following the rule that every process with children must have exactly two children. All 7 processes print their own PID, the PID of its parent, and the PIDs of all its children, as returned from fork() or wait(0). Use getpid() and getppid() to get process IDs as appropriate.


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;

    printf("Parent pid %d\n", getpid());

    pid1 = fork();  // First child of the parent
    if (pid1 == 0) {  // Child 1
        printf("Child 1 pid %d from parent pid %d\n", getpid(), getppid());

        pid3 = fork();  // First child of Child 1
        if (pid3 == 0) {  // Grandchild (Child 3)
            printf("Child 3 pid %d from parent pid %d\n", getpid(), getppid());
            exit(0);
        } else {
            pid4 = fork();  // Second child of Child 1
            if (pid4 == 0) {  // Grandchild (Child 4)
                printf("Child 4 pid %d from parent pid %d\n", getpid(), getppid());
                exit(0);
            } else {
                printf("Child 1 has two children: %d and %d\n", pid3, pid4);  // Print PIDs of children of Child 1
                wait(NULL);  // Wait for child 3
                wait(NULL);  // Wait for child 4
            }
        }
        exit(0);  // Child 1 exits
    } else {
        pid2 = fork();  // Second child of the original parent
        if (pid2 == 0) {  // Child 2
            printf("Child 2 pid %d from parent pid %d\n", getpid(), getppid());

            pid5 = fork();  // First child of Child 2
            if (pid5 == 0) {  // Grandchild (Child 5)
                printf("Child 5 pid %d from parent pid %d\n", getpid(), getppid());
                exit(0);
            } else {
                pid6 = fork();  // Second child of Child 2
                if (pid6 == 0) {  // Grandchild (Child 6)
                    printf("Child 6 pid %d from parent pid %d\n", getpid(), getppid());
                    exit(0);
                } else {
                    printf("Child 2 has two children: %d and %d\n", pid5, pid6);  // Print PIDs of children of Child 2
                    wait(NULL);  // Wait for child 5
                    wait(NULL);  // Wait for child 6
                }
            }
            exit(0);  // Child 2 exits
        } else {
            printf("Original parent has two children: %d and %d\n", pid1, pid2);  // Print PIDs of children of the original parent
            wait(NULL);  // Wait for child 1
            wait(NULL);  // Wait for child 2
        }
    }

    return 0;
}