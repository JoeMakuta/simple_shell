#include "entry.h"

/**
 * _numlen - Get the lenght of a number.
 * @number: type int number.
 * Return: Lenght of a number.
 */
int _numlen(int number)
{
	unsigned int n;
	int lenght = 1;

	if (number < 0)
	{
		lenght++;
		n = number * -1;
	}
	else
	{
		n = number;
	}
	while (n > 9)
	{
		lenght++;
		n = n / 10;
	}

	return (lenght);
}

/**
 * _itoa - Converts int to string.
 * @number: The int number
 * Return: A string.
 */
char *_itoa(int number)
{
	unsigned int n;
	int lenght = _numlen(number);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (number < 0)
	{
		n = number * -1;
		buffer[0] = '-';
	}
	else
	{
		n = number;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n % 10) + '0';
		n = n / 10;
		lenght--;
	}
	while (n > 0)
		;
	return (buffer);
}

/**
 * _atoi - Converts a string to an integer.
 * @string: The input string.
 * Return: integer.
 */
int _atoi(char *string)
{
	unsigned int c = 0, size = 0, o = 0, p = 1, m = 1, i;

	while (*(string + c) != '\0')
	{
		if (size > 0 && (*(string + c) < '0' || *(string + c) > '9'))
			break;

		if (*(string + c) == '-')
			p *= -1;

		if ((*(string + c) >= '0') && (*(string + c) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		c++;
	}

	for (i = c - size; i < c; i++)
	{
		o = o + ((*(string + i) - 48) * m);
		m /= 10;
	}
	return (o * p);
}
