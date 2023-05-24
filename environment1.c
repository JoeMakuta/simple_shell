#include "entry.h"

/**
 * cpy_inf - copies info to create as vars or alias
 * @name: The name
 * @val: The value
 *
 * Return: new env or alias.
 */
char *cpy_inf(char *name, char *val)
{
	char *new;
	int lenn, lenv, len;

	lenv = _strlen(val);
	lenn = _strlen(name);
	len = lenn + lenv + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, val);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @val: The value of the environment variable
 * @data: data structure (environ)
 * Return: Nothing
 */
void set_env(char *name, char *val, data_t *data)
{
	int i;
	char *_env, *n_env;

	for (i = 0; data->_environ[i]; i++)
	{
		_env = _strdup(data->_environ[i]);
		n_env = _strtok(_env, "=");
		if (_strcmp(n_env, name) == 0)
		{
			free(data->_environ[i]);
			data->_environ[i] = cpy_inf(n_env, val);
			free(_env);
			return;
		}
		free(_env);
	}

	data->_environ = _rallocdp(data->_environ, i, sizeof(char *) * (i + 2));
	data->_environ[i] = cpy_inf(name, val);
	data->_environ[i + 1] = NULL;
}

/**
 * _cmp_env - compares env variables names bfr setting
 * with the name passed.
 * @data: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _cmp_env(data_t *data)
{

	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		_error(data, -1);
		return (1);
	}

	set_env(data->args[1], data->args[2], data);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @data: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_t *data)
{
	char **raloc_environ;
	char *_env, *n_env;
	int i, j, k;

	if (data->args[1] == NULL)
	{
		_error(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->_environ[i]; i++)
	{
		_env = _strdup(data->_environ[i]);
		n_env = _strtok(_env, "=");
		if (_strcmp(n_env, data->args[1]) == 0)
		{
			k = i;
		}
		free(_env);
	}
	if (k == -1)
	{
		_error(data, -1);
		return (1);
	}
	raloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->_environ[i]; i++)
	{
		if (i != k)
		{
			raloc_environ[j] = data->_environ[i];
			j++;
		}
	}
	raloc_environ[j] = NULL;
	free(data->_environ[k]);
	free(data->_environ);
	data->_environ = raloc_environ;
	return (1);
}
