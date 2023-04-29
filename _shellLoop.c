#include "main.h"
/**
 * loop - shell loop
 * @info: structure
 * @a: argument
 * Return: always 1
 */
int loop(info_t *info, char **a)
{
	int builtin_ret = 0;
	ssize_t r = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
		{
			_puts("$ ");
		}
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			if (is_builtin(info))
			{
				builtin_ret = run_builtin(info);
			}
			else if (is_executable(info))
			{
				run_executable(info);
			}
			else if (is_directory(info))
			{
				print_error(info, "is a directory\n");
				info->status = 126;
			}
			else
			{
				print_error(info, "not found\n");
				info->status = 127;
			}
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
		}
		exit(info->err_num);
	}
	return builtin_ret;
}
/**
 * is_builtin - checks if the command is a builtin
 * @info: structure
 * Return: Always true
 */
bool is_builtin(info_t *info)
{
	static const char *builtins[] = {
		"cd", "env", "exit", "help", "history", "setenv", "unsetenv", NULL
	};
	int i;

	for (i = 0; builtins[i]; i++)
	{
		if (_strcmp(info->argv[0], builtins[i]) == 0)
			return (true);
	}
	return (false);
}
/**
 * run_builtin - runs a builtin command
 * @info: structure
 * Return: Always 1
 */
int run_builtin(info_t *info)
{
	static const builtin_func_t builtins[] = {
		{"cd", builtin_cd},
		{"env", builtin_env},
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"history", builtin_history},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{NULL, NULL}
	};
	int i, ret;

	for (i = 0; builtins[i].name; i++)
	{
		if (_strcmp(info->argv[0], builtins[i].name) == 0)
		{
			info->line_count++;
			ret = builtins[i].func(info);
			return (ret);
		}
	}
	return (-1);
}
/**
 * is_executable - checks if the command is an executable file
 * @info: structure
 * Return: alway true
 */

