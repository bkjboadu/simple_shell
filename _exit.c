#include "main.h"
/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcode = 0;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcode = atoi(info->argv[1]);
		if (exitcode == 0 && strcmp(info->argv[1], "0") != 0)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
	}
	exit(exitcode);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir = NULL;
	char buffer[1024];

	if (!info->argv[1])
	{
		dir = getenv("HOME");
		if (!dir)
			dir = "/";
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (!dir)
		{
			_puts("bash: cd: OLDPWD not set\n");
			return (1);
		}
		_puts(dir), _putchar('\n');
	}
	else
		dir = info->argv[1];
	if (chdir(dir) == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir), _eputchar('\n');
	}
	else
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(buffer, 1024), 1);
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
