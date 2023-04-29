#include "main.h"
/**
 * print_list_str - prints the current environment
 * @head: structure
 * Return: Always 0
 */
void print_list_str(list_t *head)
{
	while (head)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}
/**
 * find_str_in_list - find the value of list
 * @head: structure
 * @str: string
 * Return: Always 0
 */
char *find_str_in_list(list_t *head, const char *str)
{
	char *p;

	while (head)
	{
		p = strstr(head->str, str);
		if (p == head->str)
			return (p + strlen(str));
		head = head->next;
	}
	return (NULL);
}
/**
 * my_setenv - Function to set environment variabe
 * @info: structure
 * Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	setenv(info->argv[1], info->argv[2], 1);
	return (0);
}
/**
 * my_unsetenv - Function to unset an environment variable
 * @info: structure
 * Return: Always 0
 */
int my_unsetenv(info_t *info)
{
	if (info->argc != 2)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}
	unsetenv(info->argv[1]);
	return (0);
}
/**
 * populate_env_list - function to populate the linked list with the env var
 * @info: structure
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	int i;

	for (i = 0; environ[i]; i++)
		add_node_end(&info->env, environ[i]);
	return (0);
}
