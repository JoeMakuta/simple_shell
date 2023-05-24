#include "entry.h"

/**
 * _builtin - performs bltin
 * @cmd: The command
 * Return: Pointer to the bltin function
 */
int (*_builtin(char *cmd))(data_t *)
{
	bltin_t bltin[] = {
		{ "cd", cd_sh },
		{ "help", _help },
		{ "exit", ext_shell },
		{ "env", _env },
		{ "setenv", _cmp_env },
		{ "unsetenv", _unsetenv },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; bltin[i].name; i++)
	{
		if (_strcmp(bltin[i].name, cmd) == 0)
			break;
	}

	return (bltin[i].f);
}
