#include "entry.h"

/**
 * swap_op - Swaps | and & operator
 *
 * @string: The string to swap
 * @type: The type of swap
 * Return: The swapped string
 */
char *swap_op(char *string, int type)
{
	int i;

	if (type == 0)
	{
		for (i = 0; string[i]; i++)
		{
			if (string[i] == '|')
			{
				if (string[i + 1] != '|')
					string[i] = 16;
				else
					i++;
			}

			if (string[i] == '&')
			{
				if (string[i + 1] != '&')
					string[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; string[i]; i++)
		{
			string[i] = (string[i] == 16 ? '|' : string[i]);
			string[i] = (string[i] == 12 ? '&' : string[i]);
		}
	}
	return (string);
}

/**
 * add_nodes - Add (separator , command line) in a linked list
 *
 * @head_se: The head of separator llist
 * @head_co: The head of command lines llist
 * @str: The input string
 * Return: Nothing
 */
void add_nodes(sep_l_t **head_se, line_list_t **head_co, char *str)
{
	int i;
	char *line;

	str = swap_op(str, 0);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ';')
			_add_sep(head_se, str[i]);

		if (str[i] == '|' || str[i] == '&')
		{
			_add_sep(head_se, str[i]);
			i++;
		}
	}

	line = _strtok(str, ";|&");
	do {
		line = swap_op(line, 1);
		_add_com(head_co, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _next - Jump to the next command line
 *
 * @list_se: The separator llist
 * @list_co: The command line llist
 * @data: The data struct
 * Return: Nothing
 */
void _next(sep_l_t **list_se, line_list_t **list_co, data_t *data)
{
	int loop_sep;
	sep_l_t *ls_se;
	line_list_t *ls_co;

	loop_sep = 1;
	ls_se = *list_se;
	ls_co = *list_co;

	while (ls_se != NULL && loop_sep)
	{
		if (data->status == 0)
		{
			if (ls_se->separator == '&' || ls_se->separator == ';')
				loop_sep = 0;
			if (ls_se->separator == '|')
				ls_co = ls_co->next, ls_se = ls_se->next;
		}
		else
		{
			if (ls_se->separator == '|' || ls_se->separator == ';')
				loop_sep = 0;
			if (ls_se->separator == '&')
				ls_co = ls_co->next, ls_se = ls_se->next;
		}
		if (ls_se != NULL && !loop_sep)
			ls_se = ls_se->next;
	}

	*list_se = ls_se;
	*list_co = ls_co;
}

/**
 * split_commands - splits command lines according to separators
 *
 * @data: The data struct
 * @string: The input string
 * Return: 1 to continue, 0 to exit
 */
int split_commands(data_t *data, char *string)
{

	sep_l_t *head_se, *list_se;
	line_list_t *head_co, *list_co;
	int loop;

	head_se = NULL;
	head_co = NULL;

	add_nodes(&head_se, &head_co, string);

	list_se = head_se;
	list_co = head_co;

	while (list_co != NULL)
	{
		data->input = list_co->line;
		data->args = tokenizer(data->input);
		loop = exc_line_cm(data);
		free(data->args);

		if (loop == 0)
			break;

		_next(&list_se, &list_co, data);

		if (list_co != NULL)
			list_co = list_co->next;
	}

	free_sep_l(&head_se);
	free_com_l(&head_co);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * tokenizer - Tokenizes the input string
 *
 * @string: input string.
 * Return: A string splitted.
 */
char **tokenizer(char *string)
{
	size_t size;
	size_t i;
	char **tokens;
	char *token;

	size = TOKEN_BUFSIZE;
	tokens = malloc(sizeof(char *) * (size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(string, TOKEN_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == size)
		{
			size += TOKEN_BUFSIZE;
			tokens = _rallocdp(tokens, i, sizeof(char *) * size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
