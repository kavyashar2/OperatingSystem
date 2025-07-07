// Name: Kavya Sharma
// Date: October 16th, 2024
// Title: Lab 4 – Step 3
// Description: Thread driven matrix multiplication

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define N 1000
#define M 1024
#define L 500

void *matrixmult(void *);

double matrixA[N][M], matrixB[M][L], matrixC[N][L];
pthread_t threads[N];

int main() {

    // Initialising matrices
	srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrixA[i][j] = rand() %10;

    srand(time(NULL));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < L; j++)
            matrixB[i][j] = rand() %10;

    /*
    printf("Matrix A:\n");
    for (int i = 0; i < N; i++) {  
        for (int j = 0; j < M; j++) {  
            printf("%.1f ", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < M; i++) { 
        for (int j = 0; j < L; j++) {  
            printf("%.1f ", matrixB[i][j]);
        }
        printf("\n");
    }
    */

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, matrixmult, (void *)(size_t)i);

	for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("\nMatrix C:\n");
    for (int i = 0; i < N; i++) {  
        for (int j = 0; j < L; j++) { 
            printf("%.1f ", matrixC[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void *matrixmult(void *arg) {
	int i = (int)(size_t)arg;

    for (int j = 0; j < L; j++) {
        double temp = 0;
        for (int k = 0; k < M; k++) {
            temp += matrixA[i][k] * matrixB[k][j];  
        }
        matrixC[i][j] = temp;
    }

    return NULL;
}
