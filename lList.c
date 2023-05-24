#include "entry.h"

/**
 * _add_sep - adds a separator found.
 * @head: The head of the llist.
 * @sp: The separator (; | &).
 * Return: The address of the head.
 */
sep_l_t *_add_sep(sep_l_t **head, char sp)
{
	sep_l_t *newll, *tmp;

	newll = malloc(sizeof(sep_l_t));
	if (newll == NULL)
		return (NULL);

	newll->separator = sp;
	newll->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = newll;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newll;
	}

	return (*head);
}

/**
 * free_sep_l - frees a sep_list
 * @head: The head of the llist.
 * Return: Nothing.
 */
void free_sep_l(sep_l_t **head)
{
	sep_l_t *tmp;
	sep_l_t *cu;

	if (head != NULL)
	{
		cu = *head;
		while ((tmp = cu) != NULL)
		{
			cu = cu->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * _add_com - adds a command line.
 * @head: The head of the linked list.
 * @line: Thecommand line.
 * Return: address of the head.
 */
line_list_t *_add_com(line_list_t **head, char *line)
{
	line_list_t *newll, *tmp;

	newll = malloc(sizeof(line_list_t));
	if (newll == NULL)
		return (NULL);

	newll->line = line;
	newll->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = newll;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newll;
	}

	return (*head);
}

/**
 * free_com_l - frees a line list.
 * @head: head of the linked list.
 * Return: Nothing.
 */
void free_com_l(line_list_t **head)
{
	line_list_t *tmp;
	line_list_t *cu;

	if (head != NULL)
	{
		cu = *head;
		while ((tmp = cu) != NULL)
		{
			cu = cu->next;
			free(tmp);
		}
		*head = NULL;
	}
}
