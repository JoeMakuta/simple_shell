#include "entry.h"

/**
 * is_cudir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @index: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cudir(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);

	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}

	if (path[*index])
		*index += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @command: command name
 * @_envron: environment variable
 * Return: location of the command.
 */
char *_which(char *command, char **_envron)
{
	char *path, *ppath, *tpath, *dr;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv_v("PATH", _envron);
	if (path)
	{
		ppath = _strdup(path);
		len_cmd = _strlen(command);
		tpath = _strtok(ppath, ":");
		i = 0;
		while (tpath != NULL)
		{
			if (is_cudir(path, &i))
				if (stat(command, &st) == 0)
					return (command);
			len_dir = _strlen(tpath);
			dr = malloc(len_dir + len_cmd + 2);
			_strcpy(dr, tpath);
			_strcat(dr, "/");
			_strcat(dr, command);
			_strcat(dr, "\0");
			if (stat(dr, &st) == 0)
			{
				free(ppath);
				return (dr);
			}
			free(dr);
			tpath = _strtok(NULL, ":");
		}
		free(ppath);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * is_exec - determines if is an executable
 *
 * @data: The data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_exec(data_t *data)
{
	struct stat st;
	int i;
	char *in;

	in = data->args[0];
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '.')
		{
			if (in[i + 1] == '.')
				return (0);
			if (in[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (in[i] == '/' && i != 0)
		{
			if (in[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(in + i, &st) == 0)
	{
		return (i);
	}
	_error(data, 127);
	return (-1);
}

/**
 * check_err_cmd - verifies  permissions to access
 *
 * @dr: destination directory
 * @data: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_err_cmd(char *dr, data_t *data)
{
	if (dr == NULL)
	{
		_error(data, 127);
		return (1);
	}

	if (_strcmp(data->args[0], dr) != 0)
	{
		if (access(dr, X_OK) == -1)
		{
			_error(data, 126);
			free(dr);
			return (1);
		}
		free(dr);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			_error(data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exc - executes command lines
 *
 * @data: data struct
 * Return: 1 on success.
 */
int cmd_exc(data_t *data)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exc;
	char *dr;
	(void) wpd;

	exc = is_exec(data);
	if (exc == -1)
		return (1);
	if (exc == 0)
	{
		dr = _which(data->args[0], data->_environ);
		if (check_err_cmd(dr, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exc == 0)
			dr = _which(data->args[0], data->_environ);
		else
			dr = data->args[0];
		execve(dr + exc, data->args, data->_environ);
	}
	else if (pd < 0)
	{
		perror(data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	return (1);
}
