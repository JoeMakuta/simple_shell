#include "entry.h"

/**
 * rd_line - reads the input string.
 *
 * @eof: return value of getline function
 * Return: input string
 */
char *rd_line(int *eof)
{
	char *string = NULL;
	size_t bufsize = 0;

	*eof = getline(&string, &bufsize, stdin);

	return (string);
}
