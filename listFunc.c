#include "main.h"
/**
 * listLen - list length
 * @head: head
 * Return: Always true
 */
size_t listLen(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
/**
 * strlist - string list
 * @head: head
 * Return: always true
 */
char **strlist(list_t *head)
{
	size_t i;
	char **strs;
	list_t *current = head;

	if (head == NULL)
		return (NULL);
	strs = malloc(sizeof(char *) * (listLen(head) + 1));
	if (strs == NULL)
		return (NULL);
	for (i = 0; current != NULL; i++)
	{
		strs[i] = strdup(current->str);
		if (strs[i] == NULL)
		{
			for (i--; (ssize_t) i >= 0; i--)
				free(strs[i]);
			free(strs);
			return (NULL);
		}
		current = current->next;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * printList - function to print list
 * @head: head
 * Return: always true
 */
size_t printList(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;

	while (current != NULL)
	{
		printf("%s\n", current->str);
		current = current->next;
		count++;
	}
	return (count);
}
/**
 * strNode - string node prefix
 * @head: Head
 * @pre: prefix string
 * @c: character
 * Return: Always true
 */
list_t *strNode(list_t *head, char *pre, char c)
{
	list_t *current = head;

	while (current != NULL)
	{
		if (starts(current->str, pre) &&
				(c == -1 || current->str[strlen(pre)] == c))
			return (current);
		current = current->next;
	}
	return (NULL);
}
/**
 * strindexOf - get index of stre
 * @head: head
 * @node: node
 * Return: always true
 */
ssize_t strindexOf(list_t *head, list_t *node)
{
	size_t index = 0;
	list_t *current = head;

	while (current != NULL)
	{
		if (current == node)
			return (index);
		current = current->next;
		index++;
	}
	return (-1);
}
