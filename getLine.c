#include "entry.h"

/**
 * set_input - assigns the input var for get_line
 * @lineptr: Buffer that store the input string
 * @buffer: str that is been called to line
 * @sl: size of line
 * @sb: size of buffer
 */
void set_input(char **lineptr, size_t *sl, char *buffer, size_t sb)
{

	if (*lineptr == NULL)
	{
		if  (sb > BUFSIZE)
			*sl = sb;

		else
			*sl = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*sl < sb)
	{
		if (sb > BUFSIZE)
			*sl = sb;
		else
			*sl = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read input from stream file
 * @lineptr: buffer that stores the input
 * @sl: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *sl, FILE *stream)
{
	int i;
	static ssize_t string;
	ssize_t rval;
	char *buf;
	char t = 'a';

	if (string == 0)
		fflush(stream);
	else
		return (-1);
	string = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && string == 0))
		{
			free(buf);
			return (-1);
		}
		if (i == 0 && string != 0)
		{
			string++;
			break;
		}
		if (string >= BUFSIZE)
			buf = _ralloc(buf, string, string + 1);
		buf[string] = t;
		string++;
	}
	buf[string] = '\0';
	set_input(lineptr, sl, buf, string);
	rval = string;
	if (i != 0)
		string = 0;
	return (rval);
}
