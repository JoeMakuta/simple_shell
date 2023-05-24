#include "entry.h"

/**
 * _strcat - Concatenates two strings
 * @dest: The destination string
 * @src: The source string
 * Return: the destination
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: The destination string
 * @src: The source string
 * Return: The string pointed to by dest
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _strcmp - Compares two strings.
 * @str1: The first string to compare
 * @str2: The second string to compare
 * Return: Always 0 if success.
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}
/**
 * _str_chr - Finds a character in a string,
 * @str: string.
 * @ch: character.
 * Return: the pointer to the first occurrence of the character ch.
 */
char *_str_chr(char *str, char ch)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == ch)
			return (str + i);
	if (*(str + i) == ch)
		return (str + i);
	return ('\0');
}
/**
 * _lenpref - Gets the length of a prefix substr.
 * @sgm: The initial segment.
 * @accpt: accepted bytes.
 * Return: The number of accepted bytes.
 */
int _lenpref(char *sgm, char *accpt)
{
	int i, j, bool;

	for (i = 0; *(sgm + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accpt + j) != '\0'; j++)
		{
			if (*(sgm + i) == *(accpt + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
