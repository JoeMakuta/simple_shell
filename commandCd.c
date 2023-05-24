#include "entry.h"

/**
 * cd_p - changes to the parent directory
 *
 * @data: data (environ)
 *
 * Return: Nothing
 */
void cd_p(data_t *data)
{
	char pwd[PATH_MAX];
	char *dr, *c_pwd, *c_strtk_cp;

	getcwd(pwd, sizeof(pwd));
	c_pwd = _strdup(pwd);
	set_env("OLDPWD", c_pwd, data);
	dr = data->args[1];
	if (_strcmp(".", dr) == 0)
	{
		set_env("PWD", c_pwd, data);
		free(c_pwd);
		return;
	}
	if (_strcmp("/", c_pwd) == 0)
	{
		free(c_pwd);
		return;
	}
	c_strtk_cp = c_pwd;
	rev_string(c_strtk_cp);
	c_strtk_cp = _strtok(c_strtk_cp, "/");
	if (c_strtk_cp != NULL)
	{
		c_strtk_cp = _strtok(NULL, "\0");

		if (c_strtk_cp != NULL)
			rev_string(c_strtk_cp);
	}
	if (c_strtk_cp != NULL)
	{
		chdir(c_strtk_cp);
		set_env("PWD", c_strtk_cp, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(c_pwd);
}

/**
 * _cd - changes to a directory given
 * by the user
 *
 * @data: data (directories)
 * Return: Nothing
 */
void _cd(data_t *data)
{
	char pwd[PATH_MAX];
	char *dr, *c_pwd, *cp_dr;

	getcwd(pwd, sizeof(pwd));

	dr = data->args[1];
	if (chdir(dr) == -1)
	{
		_error(data, 2);
		return;
	}

	c_pwd = _strdup(pwd);
	set_env("OLDPWD", c_pwd, data);

	cp_dr = _strdup(dr);
	set_env("PWD", cp_dr, data);

	free(c_pwd);
	free(cp_dr);

	data->status = 0;

	chdir(dr);
}

/**
 * cd_prev - changes to the previous directory
 *
 * @data: data (environ)
 * Return: NOthing
 */
void cd_prev(data_t *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_opw, *c_pwd, *c_opw;

	getcwd(pwd, sizeof(pwd));
	c_pwd = _strdup(pwd);

	p_opw = _getenv_v("OLDPWD", data->_environ);

	if (p_opw == NULL)
		c_opw = c_pwd;
	else
		c_opw = _strdup(p_opw);

	set_env("OLDPWD", c_pwd, data);

	if (chdir(c_opw) == -1)
		set_env("PWD", c_pwd, data);
	else
		set_env("PWD", c_opw, data);

	p_pwd = _getenv_v("PWD", data->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(c_pwd);
	if (p_opw)
		free(c_opw);

	data->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes to h directory
 *
 * @data: data (environ)
 * Return: Nothing
 */
void cd_home(data_t *data)
{
	char *p_pwd, *h;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	h = _getenv_v("HOME", data->_environ);

	if (h == NULL)
	{
		set_env("OLDPWD", p_pwd, data);
		free(p_pwd);
		return;
	}

	if (chdir(h) == -1)
	{
		_error(data, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, data);
	set_env("PWD", h, data);
	free(p_pwd);
	data->status = 0;
}
