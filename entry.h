#ifndef _MAIN_H_
#define _MAIN_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TOKEN_BUFSIZE 128
#define BUFSIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct sep_list - A single linked list
 * @separator: ; | &
 * @next: next node
 * Description: The linked list to store separators
 */
typedef struct sep_l
{
	char separator;
	struct sep_l *next;
} sep_l_t;

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_t;

/**
 * struct line_list - A single linked list
 * @line: command line
 * @next: next node
 * Description: The single linked list to store command lines
 */
typedef struct line_list
{
	char *line;
	struct line_list *next;
} line_list_t;

/**
 * struct rvar_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct rvar_l
{
	int len_var;
	char *val;
	int len_val;
	struct rvar_l *next;
} rvar_t;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct bltin_s
{
	char *name;
	int (*f)(data_t *datash);
} bltin_t;

/* cmd_exec.c */
int is_cudir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_exec(data_t *datash);
int check_err_cmd(char *dir, data_t *datash);
int cmd_exc(data_t *datash);

/* aux_lists.c */
sep_l_t *_add_sep(sep_l_t **head, char sep);
void free_sep_l(sep_l_t **head);
line_list_t *_add_com(line_list_t **head, char *line);
void free_com_l(line_list_t **head);

/* aux_lists2.c */
rvar_t *_add_rvar(rvar_t **head, int lvar, char *var, int lval);
void free_rvar_l(rvar_t **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_str3.c */
void rev_string(char *s);
/* check_syntax_error.c */
int count_char(char *input, int i);
int error_sy(char *input, int i, char last);
int f_char(char *input, int *i);
void print_sy_err(data_t *datash, char *input, int i, int bool);
int check_sy_err(data_t *datash, char *input);

/* aux_mem.c */
void _mcpy(void *newptr, const void *ptr, unsigned int size);
void *_ralloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_rallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chr(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* read_line.c */
char *rd_line(int *i_eof);

/* shell_loop.c */
char *remove_comment(char *in);
void shell_loop(data_t *datash);

/* split.c */
char *swap_op(char *string, int type);
void add_nodes(sep_l_t **head_s, line_list_t **head_l, char *input);
void _next(sep_l_t **list_s, line_list_t **list_l, data_t *datash);
int split_commands(data_t *data, char *string);
char **tokenizer(char *string);

/* rep_var.c */
void is_env(rvar_t **h, char *in, data_t *data);
int check_dol(rvar_t **h, char *in, char *st, data_t *data);
char *repl_string(rvar_t **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_t *datash);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exc_line_cm(data_t *datash);

/* env1.c */
char *_getenv_v(const char *name, char **_environ);
int _env(data_t *datash);

/* env2.c */
char *cpy_inf(char *name, char *value);
void set_env(char *name, char *value, data_t *datash);
int _cmp_env(data_t *datash);
int _unsetenv(data_t *datash);

/* cd.c */
void cd_p(data_t *datash);
void _cd(data_t *datash);
void cd_prev(data_t *datash);
void cd_home(data_t *datash);

/* cd_shell.c */
int cd_sh(data_t *datash);

/* get_builtin */
int (*_builtin(char *cmd))(data_t *datash);

/* _exit.c */
int ext_shell(data_t *datash);

/* aux_stdlib.c */
int _numlen(int n);
char *_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(data_t *, char *, char *, char *);
char *get_cd_err(data_t *datash);
char *not_found_err(data_t *datash);
char *exit_sh_err(data_t *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *e_env(data_t *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *e_path_126(data_t *datash);

/* aux_help2.c */
void _help_bltin(void);
void _help_alias(void);
void _help_cd(void);

/* get_error.c */
int _error(data_t *datash, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void _help_env(void);
void _help_setenv(void);
void _help_unsetenv(void);
void _help_gen(void);
void _help_exit(void);

/* get_help.c */
int _help(data_t *datash);

#endif