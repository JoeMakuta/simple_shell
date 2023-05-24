#include "entry.h"

/**
 * _strdup - duplicates a string.
 * @string: Type char pointer string
 * Return: duplicated string
 */
char *_strdup(const char *string)
{
	char *new_str;
	size_t len;

	len = _strlen(string);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	_mcpy(new_str, string, len + 1);
	return (new_str);
}

/**
 * _strlen - Returns the lenght of a string.
 * @string: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *string)
{
	int len;

	for (len = 0; string[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chr - compare chars of strings
 * @string: The input string.
 * @del: The delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chr(char string[], const char *del)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; string[i]; i++)
	{
		for (j = 0; del[j]; j++)
		{
			if (string[i] == del[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - breaks a string down into tokens.
 * @string: The input string.
 * @del: The delimiter.
 *
 * Return: Tokens.
 */
char *_strtok(char string[], const char *del)
{
	static char *splitted, *str_e;
	char *str_s;
	unsigned int i, bl;

	if (string != NULL)
	{
		if (cmp_chr(string, del))
			return (NULL);
		splitted = string;
		i = _strlen(string);
		str_e = &string[i];
	}
	str_s = splitted;
	if (str_s == str_e)
		return (NULL);

	for (bl = 0; *splitted; splitted++)
	{
		if (splitted != str_s)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; del[i]; i++)
		{
			if (*splitted == del[i])
			{
				*splitted = '\0';
				if (splitted == str_s)
					str_s++;
				break;
			}
		}
		if (bl == 0 && *splitted)
			bl = 1;
	}
	if (bl == 0)
		return (NULL);
	return (str_s);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @string: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *string)
{
	unsigned int i;

	for (i = 0; string[i]; i++)
	{
		if (string[i] < 48 || string[i] > 57)
			return (0);
	}
	return (1);
}
