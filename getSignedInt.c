#include "entry.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sing: Signal handler
 */
void get_sigint(int sing)
{
	(void)sing;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
