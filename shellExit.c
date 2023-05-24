#include "entry.h"

/**
 * ext_shell - exits the shell
 * @data: data relevant (status and args)
 * Return: 0 on success.
 */
int ext_shell(data_t *data)
{
	unsigned int ust;
	int is_dg;
	int len;
	int bg;

	if (data->args[1] != NULL)
	{
		len = _strlen(data->args[1]);
		ust = _atoi(data->args[1]);
		is_dg = _isdigit(data->args[1]);
		bg = ust > (unsigned int)INT_MAX;
		if (!is_dg || len > 10 || bg)
		{
			_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (ust % 256);
	}
	return (0);
}
