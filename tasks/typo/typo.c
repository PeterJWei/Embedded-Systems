/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	/* Add code here -- put your names at the top. */

	char b[255];
	int r, s, sd;
	unsigned long start, total;

	while(1) {
		print("Enter text >");
		start = time();
		
		//read input and null terminate
		r=read(STDIN_FILENO, b, 255);
		if (r<1) continue;
		b[r-1] = 0;

		//calculate time
		total = time() - start;
		s = total/1000;
		sd = (total - (s*1000))/100;

		printf("%s\n%d.%d\n", b,s, sd);
	}

	return 0;
}
