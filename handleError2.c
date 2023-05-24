#include "entry.h"

/**
 * e_env - error message for env.
 * @data: data relevant (counter, arguments)
 * Return: The error message.
 */
char *e_env(data_t *data)
{
	int len;
	char *err;
	char *msg;
	char *v_str;

	v_str = _itoa(data->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(data->av[0]) + _strlen(v_str);
	len += _strlen(data->args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(v_str);
		return (NULL);
	}

	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, v_str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, msg);
	_strcat(err, "\0");
	free(v_str);

	return (err);
}
/**
 * e_path_126 - err message for failure (path and denied permission).
 * @data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *e_path_126(data_t *data)
{
	int len;
	char *v_str;
	char *err;

	v_str = _itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(v_str);
	len += _strlen(data->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(v_str);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, v_str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(v_str);
	return (err);
}
