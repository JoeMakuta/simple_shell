#include "entry.h"

/**
 * _help - function that retrieves help messages according builtin
 * @data: data structure (args and input)
 * Return: Return 0
*/
int _help(data_t *data)
{

	if (data->args[1] == 0)
		_help_gen();
	else if (_strcmp(data->args[1], "help") == 0)
		_help_bltin();
	else if (_strcmp(data->args[1], "cd") == 0)
		_help_cd();
	else if (_strcmp(data->args[1], "setenv") == 0)
		_help_setenv();
	else if (_strcmp(data->args[1], "env") == 0)
		_help_env();
	else if (_strcmp(data->args[1], "unsetenv") == 0)
		_help_unsetenv();
	else if (_strcmp(data->args[1], "exit") == 0)
		_help_exit();
	else if (_strcmp(data->args[1], "alias") == 0)
		_help_alias();
	else
		write(STDERR_FILENO, data->args[0],
		      _strlen(data->args[0]));

	data->status = 0;
	return (1);
}
