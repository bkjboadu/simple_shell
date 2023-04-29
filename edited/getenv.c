#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *		  constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (info->environ == NULL || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *		constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	size_t index = 0;
	list_t *node = info->env;

	if (!info || !info->env || !var)
		return (0);

	while (node)
	{
		char *p = starts_with(node->str, var);

		if (p != NULL && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			node = info->env;
			index = 0;
		} else
		{
			node = node->next;
			index++;
		}
	}

	return (info->env_changed);
}


/**
 * _setenv - Initialize a new environment variable,
 *					   or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *			  constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *env_var, *p;
	list_t *node;

	if (!var || !value)
		return (0);
	env_var = malloc(strlen(var) + strlen(value) + 2);
	if (!env_var)
		return (0);
	p = env_var;
	while (*var)
		*p++ = *var++;
	*p++ = '=';
	while (*value)
		*p++ =  *value++;
	*p = '\0';
	for (node = info->env; node; node = node->next)
	{
		char *str = node->str;
		char *q = env_var;

		while (*str && *str != '=')
		{
			if (*str != *q)
				break;
			str++;
			q++;
		}
		if (*str == '=' && *q == '\0')
		{
			free(node->str);
			node->str = env_var;
			info->env_changed = 1;
			return (0);
		}
	}
	add_node_end(&(info->env), env_var, 0);
	info->env_changed = 1;
	return (0);
}
