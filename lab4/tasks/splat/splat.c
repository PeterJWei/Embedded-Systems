/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 * 
 * Group 17
 * Names: Peter Wei <pwei@andrew.cmu.edu>
 *        Vruti Sivakumaran <vsivakum@andrew.cmu.edu>
 */

#include <unistd.h>
#include <stdio.h>

int main()
{
	//All the symbols to be printed
	char s[] = {'|', '/', '-', '\\'};
	int i = 1;
	
	//Initial cursor
	putchar('|');
	sleep(200);

	//Loop and switch cursor every 200ms
	while (1) {
	   putchar('\b');
	   putchar(s[i]);

	   if (++i == 4) i=0;
	   sleep(200);
	}
	return 0;
}
