// Name: Kavya Sharma
// Date: 13th November, 2024
// Title: Lab8 – Second CHance Algorithm
// Description: Page replacement algorithm that gives every page a second chance in the sense that any page that has been the cause of a cache hit is likely going to cause further cache hits, and therefore, should not be swapped out in place of a newer page that has never caused a cache hit.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	int pageno;
	int chance;
} ref_page;

int main(int argc, char *argv[])
{
	int C_SIZE = atoi(argv[1]); // Cache size from command-line argument
	ref_page cache[C_SIZE];		// Array to store cache pages
	char pageCache[100];		// Buffer for page read from input

	int i, j;
	int totalFaults = 0; // Tracks total page faults
	int counter = 0;	 // Points to the next page for potential replacement
	int totalRequests = 0;

	// Initialize the cache with empty pages (-1) and chance bits to 0
	for (i = 0; i < C_SIZE; i++)
	{
		cache[i].pageno = -1;
		cache[i].chance = 0;
	}

	// Read each page reference from standard input
	while (fgets(pageCache, sizeof(pageCache), stdin))
	{
		int page_num = atoi(pageCache); // Convert page reference to integer
		totalRequests++;
		int found = 0;

		// Step 1: Check if the page is already in the cache
		for (i = 0; i < C_SIZE; i++)
		{
			if (cache[i].pageno == page_num)
			{						 // Page is found in cache
				cache[i].chance = 1; // Give it a second chance
				found = 1;
				break;
			}
		}

		// Step 2: Page not found in cache (Page Fault)
		if (!found)
		{
			totalFaults++;

			// Second Chance Replacement policy
			while (1)
			{
				// If chance bit is 0, replace this page
				if (cache[counter].chance == 0)
				{
					cache[counter].pageno = page_num; // Replace page number
					// cache[counter].chance = 1;		  // Set second chance bit
					counter = (counter + 1) % C_SIZE; // Move to next slot in circular way
					break;
				}
				else
				{
					// If chance bit is 1, reset it and move to the next page
					cache[counter].chance = 0;
					counter = (counter + 1) % C_SIZE; // Move to the next slot
				}
			}
		}
	}

	// Output total page faults only for the test result consistency
	printf("%d\n", totalFaults);

	return 0;
}
