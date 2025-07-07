// Name: Kavya Sharma
// Date: 20th November, 2024
// Title: Lab 9 – Part 3
// Description:  A copy of the program from Step 2, modified to measure the I/O performance for 100, 1,000, 10,000 and 100,000 bytes of buffer sizes.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char buffer[atoi(argv[2])]; // buffer with size specified by argv[2]
	FILE *fp;
	fp = fopen(argv[1], "rb"); // open file specified by argv[1]
	while (fread(buffer, sizeof(buffer), 1, fp))
	{ // read the contents of the file into the buffer
	}
	fclose(fp);
	return 0;
}
