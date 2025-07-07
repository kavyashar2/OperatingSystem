// Name: Kavya Sharma
// Date: 13th November, 2024
// Title: Lab8 – Least Recently Used Algorithm
// Description: Page replacement algorithm that replaces the page that was last used (hit or miss) at the earliest point in time.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int pageno; // Page number in the cache
    int index;  // Keeps track of recency of use (higher values are older)
} ref_page;

int main(int argc, char *argv[])
{
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user as a command-line argument
    ref_page cache[C_SIZE];     // Cache array to store pages
    char pageCache[100];        // Buffer for reading input pages

    int i, j;
    int totalFaults = 0;   // Counter for total page faults
    int oldest;            // Tracks the oldest page index
    int oldestPos;         // Position of the oldest page
    int totalRequests = 0; // Total number of page requests

    // Initialize cache with empty pages (-1 indicates an empty slot)
    for (i = 0; i < C_SIZE; i++)
    {
        cache[i].pageno = -1;
        cache[i].index = 0;
    }

    // Read each page number from standard input
    while (fgets(pageCache, 100, stdin))
    {
        int page_num = atoi(pageCache); // Convert page number from string to int
        totalRequests++;

        // Check if page_num is already in the cache
        for (i = 0; i < C_SIZE; i++)
        {
            oldest = cache[i].index; // Temporarily store the index for comparison
            if (cache[i].pageno == page_num)
            { // Page hit
                // Update indices: Increment all indices except the one that matched
                for (j = 0; j < C_SIZE; j++)
                {
                    if (cache[j].index < cache[i].index)
                    {
                        cache[j].index++;
                    }
                }
                cache[i].index = 0; // Reset index of the recently accessed page
                break;
            }
            else if (i == C_SIZE - 1)
            {                  // Page miss (end of array)
                totalFaults++; // Increment page fault counter

                // Update all indices, marking all pages as older
                for (j = 0; j < C_SIZE; j++)
                {
                    cache[j].index++;
                }

                // Find the oldest page (one with the highest index)
                oldest = -1;
                for (j = 0; j < C_SIZE; j++)
                {
                    if (cache[j].index > oldest)
                    {
                        oldest = cache[j].index;
                        oldestPos = j; // Position of the oldest page
                    }
                }

                // Replace the oldest page with the new page
                cache[oldestPos].pageno = page_num;
                cache[oldestPos].index = 0; // Reset index of the newly added page
            }
        }
    }

    // Output only the total page faults for the large test file
    printf("%d\n", totalFaults);

    return 0;
}
