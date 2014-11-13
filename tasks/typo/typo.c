/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 * 
 * Group 17
 * 
 * Names: Peter Wei <pwei@andrew.cmu.edu>
 *	  Vruti Sivakumaran <vsivakum@andrew.cmu.edu>
 */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	char b[255];
	int r;
	unsigned long start, total, s, sd;

	while(1) {
		//Display prompt and record start time
		printf("Enter text >");
		start = time();
		
		//read input and null terminate
		r=read(STDIN_FILENO, b, 255);
                write(STDOUT_FILENO, b, r);
		if (r<1) continue;
		b[r-1] = 0;

		//calculate time
		total = time() - start;
		s = total/1000;
		sd = (total - (s*1000))/100;

                printf("%lu", s);
                printf(".");
                printf("%lu", sd);
                printf("s\n");
	}

	return 0;
}
