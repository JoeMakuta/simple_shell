#include "entry.h"

/**
 * strcat_cd - concatenates the message for cd error
 *
 * @data: Thedata (directory)
 * @msg: The message to print
 * @err: THe output message
 * @c_line: The lines counter
 * Return: err message
 */
char *strcat_cd(data_t *data, char *msg, char *err, char *c_line)
{
	char *il_flag;

	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, c_line);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, msg);
	if (data->args[1][0] == '-')
	{
		il_flag = malloc(3);
		il_flag[0] = '-';
		il_flag[1] = data->args[1][1];
		il_flag[2] = '\0';
		_strcat(err, il_flag);
		free(il_flag);
	}
	else
	{
		_strcat(err, data->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * get_cd_err - The error message for cd command in get_cd
 * @data: The data (directory)
 * Return: The error message
 */
char *get_cd_err(data_t *data)
{
	int len, len_id;
	char *err, *c_line, *msg;

	c_line = _itoa(data->counter);
	if (data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(data->args[1]);
	}

	len = _strlen(data->av[0]) + _strlen(data->args[0]);
	len += _strlen(c_line) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(c_line);
		return (NULL);
	}

	err = strcat_cd(data, msg, err, c_line);

	free(c_line);

	return (err);
}

/**
 * not_found_err - The error message for command not found
 * @data: The data (counter, arguments)
 * Return: Error message
 */
char *not_found_err(data_t *data)
{
	int len;
	char *err;
	char *c_line;

	c_line = _itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(c_line);
	len += _strlen(data->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(c_line);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, c_line);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(c_line);
	return (err);
}

/**
 * exit_sh_err - The error message for exit shell
 * @data: The data (counter, arguments)
 *
 * Return: Error message
 */
char *exit_sh_err(data_t *data)
{
	int len;
	char *err;
	char *c_line;

	c_line = _itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(c_line);
	len += _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(c_line);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, c_line);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, data->args[1]);
	_strcat(err, "\n\0");
	free(c_line);

	return (err);
}
