#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[sizeof(int)];
    int i;
    int numRequests = 20;
    int possiblePages = 10;

    // Open file in write mode
    fp = fopen("testInput.txt", "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Generate random page requests and write to file
    for (i = 0; i < numRequests; i++)
    {
        sprintf(buffer, "%d\n", rand() % possiblePages);
        fputs(buffer, fp);
    }

    // Close file
    fclose(fp);
    printf("testInput.txt generated with %d page requests.\n", numRequests);

    return 0;
}
