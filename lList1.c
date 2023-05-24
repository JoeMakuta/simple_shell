#include "entry.h"

/**
 * _add_rvar - adds a variable at the end.
 * @head: The head of the llist.
 * @lenv: The length of the variable.
 * @val: The value of the variable.
 * @lenva: length of the value.
 * Return: The address of the head.
 */
rvar_t *_add_rvar(rvar_t **head, int lenv, char *val, int lenva)
{
	rvar_t *new, *tmp;

	new = malloc(sizeof(rvar_t));
	if (new == NULL)
		return (NULL);

	new->len_var = lenv;
	new->val = val;
	new->len_val = lenva;

	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_rvar_l - frees a rvar_t llist.
 * @head: The head of the llist.
 * Return: Nothing.
 */
void free_rvar_l(rvar_t **head)
{
	rvar_t *tmp;
	rvar_t *cu;

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
