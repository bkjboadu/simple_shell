#include "main.h"
/**
 * _shellhistory - functions for alias
 * @info: structure
 * Return: Always 1
 */
int _shellhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - function to set alia to string
 * @info: structure
 * @str: string
 * Return: Always true
 */
int unset_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	char c = *p;
	*p = 0;
	int ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0
 */
int set_alias(info_t *info, char *str)
{
	char *key = strtok(str, "=");
	char *value = strtok(NULL, "");

	if (!key || !value)
	{
		return (1);
	}
	unset_alias(info, str);
	char *new_str = malloc(strlen(str) + 1);
	if (!new_str)
	{
		return (1);
	}
	strcpy(new_str, str);
	strcat(new_str, "=");
	strcat(new_str, value);
	return (add_node_end(&(info->alias), new_str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0
 */
int print_alias(list_t *node)
{
	if (node == NULL)
	{
		return (1);
	}
	char *delim = strchr(node->str, '=');

	if (delim == NULL)
	{
		return (1);
	}
	printf("%.*s'%s'\n", (int)(delim - node->str), node->str, delim + 1);
	return (0);
}
/**
 *  _myalias - mimics the alias builtin (man alias)
 *  @info: structure
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int y = 0;
	char *value = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	y = 1;
	while (info->argv[y])
	{
		value = _strchr(info->argv[y], '=');
		if (value)
			set_alias(info, info->argv[y]);
		else
			print_alias(node_starts_with(info->alias, info->argv[y], '='));
		y++;
	}
	return (0);
}
