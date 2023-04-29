#include "shell.h"

/**
 * list_len - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *head)
{
	size_t length = 0;

	while (head != NULL)
	{
		length++;
		head = head->next;
	}
	return (length);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t num_strings = list_len(head);
	size_t i, j;
	char **strings = malloc(sizeof(char *) * (num_strings + 1));

	if (!strings)
		return (NULL);
	for (i = 0; i < num_strings; i++)
	{
		size_t string_len = _strlen(head->str);
		char *string = malloc(string_len + 1);

		if (!string)
		{
			for (j = 0; j < i; j++)
			{
				free(strings[j]);
			}
			free(strings);
			return (NULL);
		}
		_strcpy(string, head->str);
		strings[i] = string;
		head = head->next;
	}
	strings[num_strings] = NULL;
	return (strings);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head != NULL)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @pf: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head, char *pf, char c)
{
	while (head != NULL)
	{
		if (starts_with(head->str, pf))
		{
			if (c == -1 || head->str[strlen(pf)] == c)
				return (head);
		}
		head = head->next;
	}

	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;
	const list_t *current;

	for (current = head; current != NULL; current = current->next)
	{
		if (current == node)
		{
			return (index);
		}
		index++;
	}

	return (-1);
}

