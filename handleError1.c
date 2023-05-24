#include "entry.h"

/**
 * _error - calls the error function according to the builtin call
 * @data: data structure that contains arguments
 * @erval: error value
 * Return: The error
 */
int _error(data_t *data, int erval)
{
	char *err;

	switch (erval)
	{
	case -1:
		err = e_env(data);
		break;
	case 2:
		if (_strcmp("exit", data->args[0]) == 0)
			err = exit_sh_err(data);
		else if (_strcmp("cd", data->args[0]) == 0)
			err = get_cd_err(data);
		break;
	case 126:
		err = e_path_126(data);
		break;
	case 127:
		err = not_found_err(data);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	data->status = erval;
	return (erval);
}
