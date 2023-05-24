#include "entry.h"

/**
 * cmp_env_n - compares env variables names
 * with the name passed.
 * @n_env: name of the environment variable
 * @name: The name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_n(const char *n_env, const char *name)
{
	int i;

	for (i = 0; n_env[i] != '='; i++)
	{
		if (n_env[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv_v - get an environment variable
 * @name: The name of the environment variable
 * @_envron: environment variable
 *
 * Return: value of the environment variable if is found.
 */
char *_getenv_v(const char *name, char **_envron)
{
	char *p_env;
	int i, m;

	p_env = NULL;
	m = 0;
	for (i = 0; _envron[i]; i++)
	{
		m = cmp_env_n(_envron[i], name);
		if (m)
		{
			p_env = _envron[i];
			break;
		}
	}

	return (p_env + m);
}

/**
 * _env - prints the evironment variables
 *
 * @data: data relevant.
 * Return: 1 on success.
 */
int _env(data_t *data)
{
	int i, j;

	for (i = 0; data->_environ[i]; i++)
	{

		for (j = 0; data->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, data->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;

	return (1);
}
