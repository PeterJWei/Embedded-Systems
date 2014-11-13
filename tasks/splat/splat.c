/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 * 
 *
 * Names: Peter Wei <pwei@andrew.cmu.edu>
 *        Vruti Sivakumaran <vsivakum@andrew.cmu.edu>
 */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	/* Add code here -- put your names at the top. */
	char s[] = {'|', '/', '-', '\\'};
	int i = 1;

	putchar('|');
	sleep(200);

	while (1) {
	   putchar('\b');
	   putchar(s[i]);

	   if (++i == 4) i=0;
	   sleep(200);
	}
	return 0;
}
