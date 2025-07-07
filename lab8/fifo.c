// Name: Kavya Sharma
// Date: 13th November, 2024
// Title: Lab8 – First in, First out Algorithm
// Description: Page replacement algorithm that keeps track of all the pages in the memory in a queue with the oldest page at the front of the queue. On a page fault, it replaces the page that has been present in memory for the longest time.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int pageno; // Page number stored in the cache
} ref_page;

int main(int argc, char *argv[])
{
    int C_SIZE = atoi(argv[1]); // Size of Cache passed as a command-line argument
    ref_page cache[C_SIZE];     // Cache array that stores page numbers
    char pageCache[100];        // Buffer to hold the input page number from stdin

    int i;
    int totalFaults = 0;   // Total page faults counter
    int placeInArray = 0;  // Index in cache for FIFO replacement
    int totalRequests = 0; // Total page requests counter

    // Initialize cache with empty pages (-1 represents an empty slot)
    for (i = 0; i < C_SIZE; i++)
    {
        cache[i].pageno = -1;
    }

    // Read each page number from stdin until end of input
    while (fgets(pageCache, 100, stdin))
    {
        int page_num = atoi(pageCache); // Convert page number from string to int
        totalRequests++;

        // Check if page_num is already in the cache
        for (i = 0; i < C_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {          // Page hit
                break; // No page fault, exit loop
            }
            if (i == C_SIZE - 1)
            {                  // Page miss
                totalFaults++; // Increment page fault counter

                // Insert page_num into cache at the current FIFO index
                cache[placeInArray].pageno = page_num;
                placeInArray++; // Move to the next FIFO position

                // Reset placeInArray if it reaches the end of cache size
                if (placeInArray == C_SIZE)
                {
                    placeInArray = 0;
                }
            }
        }
    }

    // Print only the total page faults if running a batch test
    printf("%d\n", totalFaults);

    return 0;
}
