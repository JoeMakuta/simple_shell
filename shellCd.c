#include "entry.h"

/**
 * cd_sh - changes current directory
 *
 * @data: The data
 * Return: 1 on success
 */
int cd_sh(data_t *data)
{
	char *dir;
	int is_h, is_h1, is_d;

	dir = data->args[1];

	if (dir != NULL)
	{
		is_h = _strcmp("$HOME", dir);
		is_h1 = _strcmp("~", dir);
		is_d = _strcmp("--", dir);
	}

	if (dir == NULL || !is_h || !is_h1 || !is_d)
	{
		cd_home(data);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_prev(data);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_p(data);
		return (1);
	}

	_cd(data);

	return (1);
}
