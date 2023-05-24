#include "entry.h"

/**
 * is_env - checks if it is a environnement variable
 *
 * @head: The head of llist
 * @str: The input string
 * @data: data structure
 * Return: Nothing
 */
void is_env(rvar_t **head, char *str, data_t *data)
{
	char **env;
	int val, j, r, ch;

	env = data->_environ;
	for (r = 0; env[r]; r++)
	{
		for (j = 1, ch = 0; env[r][ch]; ch++)
		{
			if (env[r][ch] == '=')
			{
				val = _strlen(env[r] + ch + 1);
				_add_rvar(head, j, env[r] + ch + 1, val);
				return;
			}

			if (str[j] == env[r][ch])
				j++;
			else
				break;
		}
	}

	for (j = 0; str[j]; j++)
	{
		if (str[j] == ' ' || str[j] == '\t' || str[j] == ';' || str[j] == '\n')
			break;
	}

	_add_rvar(head, j, NULL, 0);
}

/**
 * check_dol - check if the variable is $$ or $?
 *
 * @head: The head of the llist
 * @string: The input string
 * @statut: The last status of the Shell
 * @data: data struct
 * Return: Nothing
 */
int check_dol(rvar_t **head, char *string, char *statut, data_t *data)
{
	int i, ls, lp;

	ls = _strlen(statut);
	lp = _strlen(data->pid);

	for (i = 0; string[i]; i++)
	{
		if (string[i] == '$')
		{
			if (string[i + 1] == '?')
				_add_rvar(head, 2, statut, ls), i++;
			else if (string[i + 1] == '$')
				_add_rvar(head, 2, data->pid, lp), i++;
			else if (string[i + 1] == '\n')
				_add_rvar(head, 0, NULL, 0);
			else if (string[i + 1] == '\0')
				_add_rvar(head, 0, NULL, 0);
			else if (string[i + 1] == ' ')
				_add_rvar(head, 0, NULL, 0);
			else if (string[i + 1] == '\t')
				_add_rvar(head, 0, NULL, 0);
			else if (string[i + 1] == ';')
				_add_rvar(head, 0, NULL, 0);
			else
				is_env(head, string + i, data);
		}
	}

	return (i);
}

/**
 * repl_string - Allow to replaces string into variables
 *
 * @head: The head of the llist
 * @string: The input string
 * @new_string: The new input string (replaced)
 * @new_len: The new length
 * Return: replaced string
 */
char *repl_string(rvar_t **head, char *string, char *new_string, int new_len)
{
	rvar_t *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < new_len; i++)
	{
		if (string[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_string[i] = string[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_string[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_string[i] = string[j];
			j++;
		}
	}

	return (new_string);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @string: The input string
 * @data: The data struct
 * Return: replaced string
 */
char *rep_var(char *string, data_t *data)
{
	rvar_t *head, *index;
	char *status, *new_string;
	int olen, nlen;

	status = _itoa(data->status);
	head = NULL;

	olen = check_dol(&head, string, status, data);

	if (head == NULL)
	{
		free(status);
		return (string);
	}

	index = head;
	nlen = 0;

	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}

	nlen += olen;

	new_string = malloc(sizeof(char) * (nlen + 1));
	new_string[nlen] = '\0';

	new_string = repl_string(&head, string, new_string, nlen);

	free(string);
	free(status);
	free_rvar_l(&head);

	return (new_string);
}
