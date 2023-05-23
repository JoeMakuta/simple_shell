#include "entry.h"

/**
 * free_d - frees data struct
 *
 * @data: The data struct
 * Return: Nothing
 */
void free_d(data_t *data)
{
	unsigned int i;

	for (i = 0; data->_environ[i]; i++)
	{
		free(data->_environ[i]);
	}

	free(data->_environ);
	free(data->pid);
}

/**
 * init_data - Initialize data structure
 *
 * @data: The data struct
 * @av: argument vector
 * Return: Nothing
 */
void init_data(data_t *data, char **av)
{
	unsigned int i;

	data->av = av;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->_environ[i] = _strdup(environ[i]);
	}

	data->_environ[i] = NULL;
	data->pid = _itoa(getpid());
}

/**
 * main - Entry point
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	data_t data;
	(void) argc;

	signal(SIGINT, get_sigint);
	init_data(&data, argv);
	shell_loop(&data);
	free_d(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
}