#include "entry.h"

/**
 * count_char - counts the repetitions of a char
 *
 * @string: The string
 * @index: index
 * Return: THe amout of char in the string
 */
int count_char(char *string, int index)
{
	if (*(string - 1) == *string)
		return (count_char(string - 1, index + 1));

	return (index);
}

/**
 * error_sy - finds syntax errors
 *
 * @string: The string
 * @index: THe index
 * @lch: The last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sy(char *string, int index, char lch)
{
	int c;

	c = 0;
	if (*string == '\0')
		return (0);

	if (*string == ' ' || *string == '\t')
		return (error_sy(string + 1, index + 1, lch));

	if (*string == ';')
		if (lch == '|' || lch == '&' || lch == ';')
			return (index);

	if (*string == '|')
	{
		if (lch == ';' || lch == '&')
			return (index);

		if (lch == '|')
		{
			c = count_char(string, 0);
			if (c == 0 || c > 1)
				return (index);
		}
	}

	if (*string == '&')
	{
		if (lch == ';' || lch == '|')
			return (index);

		if (lch == '&')
		{
			c = count_char(string, 0);
			if (c == 0 || c > 1)
				return (index);
		}
	}

	return (error_sy(string + 1, index + 1, *string));
}

/**
 * f_char - finds index of the first char
 *
 * @string: The string
 * @index: index
 * Return: 1 if there is an error. 0 in other case.
 */
int f_char(char *string, int *index)
{

	for (*index = 0; string[*index]; *index += 1)
	{
		if (string[*index] == ' ' || string[*index] == '\t')
			continue;

		if (string[*index] == ';' || string[*index] == '|' || string[*index] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_sy_err - prints when a syntax error is found
 *
 * @data: data structure
 * @string: string string
 * @index: index of the err
 * @merr:  control messag err
 * Return: Nothing
 */
void print_sy_err(data_t *data, char *string, int index, int merr)
{
	char *m, *m2, *m3, *err, *counter;
	int length;

	if (string[index] == ';')
	{
		if (merr == 0)
			m = (string[index + 1] == ';' ? ";;" : ";");
		else
			m = (string[index - 1] == ';' ? ";;" : ";");
	}

	if (string[index] == '|')
		m = (string[index + 1] == '|' ? "||" : "|");

	if (string[index] == '&')
		m = (string[index + 1] == '&' ? "&&" : "&");

	m2 = ": Syntax err: \"";
	m3 = "\" unexpected\n";
	counter = _itoa(data->counter);
	length = _strlen(data->av[0]) + _strlen(counter);
	length += _strlen(m) + _strlen(m2) + _strlen(m3) + 2;

	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, counter);
	_strcat(err, m2);
	_strcat(err, m);
	_strcat(err, m3);
	_strcat(err, "\0");

	write(STDERR_FILENO, err, length);
	free(err);
	free(counter);
}

/**
 * check_sy_err - Find and print syntax error
 *
 * @data: data structure
 * @string: The input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_sy_err(data_t *data, char *string)
{
	int bg = 0;
	int _ch = 0;
	int i = 0;

	_ch = f_char(string, &bg);
	if (_ch == -1)
	{
		print_sy_err(data, string, bg, 0);
		return (1);
	}

	i = error_sy(string + bg, 0, *(string + bg));
	if (i != 0)
	{
		print_sy_err(data, string, bg + i, 1);
		return (1);
	}

	return (0);
}
