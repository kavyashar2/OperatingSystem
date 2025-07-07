// Name: Kavya Sharma
// Date: 20th November, 2024
// Title: Lab 9 – Part 4
// Description:  A copy of the program in Step 3, modified so that a write operation is made to a newly created file for each read operation.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char buffer[atoi(argv[2])]; // buffer with size speicified by argv[2]
	FILE *fp;
	fp = fopen(argv[1], "rb"); // open file specified by argv[1]
	FILE *fpout;
	fpout = fopen("output.txt", "wb"); // output file
	while (fread(buffer, sizeof(buffer), 1, fp))
	{											  // read in contents of argv[1] into the buffer
		fwrite(buffer, sizeof(buffer), 1, fpout); // write the contents of buffer into output file
	}
	fclose(fp);
	fclose(fpout);
	return 0;
}
