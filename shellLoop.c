#include "entry.h"

/**
 * remove_comment - Deletes comments from the input
 *
 * @string: The input string
 * Return: String without comments
 */
char *remove_comment(char *string)
{
	int i, up;

	up = 0;
	for (i = 0; string[i]; i++)
	{
		if (string[i] == '#')
		{
			if (i == 0)
			{
				free(string);
				return (NULL);
			}

			if (string[i - 1] == ' ' || string[i - 1] == '\t' || string[i - 1] == ';')
				up = i;
		}
	}

	if (up != 0)
	{
		string = _ralloc(string, i, up + 1);
		string[up] = '\0';
	}

	return (string);
}

/**
 * shell_loop - Loop of shell
 * @data: The data struct
 *
 * Return: Nothing.
 */
void shell_loop(data_t *data)
{
	int loop, eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = rd_line(&eof);
		if (eof != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (check_sy_err(data, input) == 1)
			{
				data->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, data);
			loop = split_commands(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
