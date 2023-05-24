#include "entry.h"

/**
 * exc_line_cm - finds builtins and commands in the typed input
 *
 * @data: data relevant (args)
 * Return: 1 on success.
 */
int exc_line_cm(data_t *data)
{
	int (*bltin)(data_t *data);

	if (data->args[0] == NULL)
		return (1);

	bltin = _builtin(data->args[0]);

	if (bltin != NULL)
		return (bltin(data));

	return (cmd_exc(data));
}
