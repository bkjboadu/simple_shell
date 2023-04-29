
#include "main.h"
/**
 * add_node - adds a command line
 * @head: address
 * @str: string
 * @num: number
 * Return: Always true
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
	{
		return (NULL);
	}
	new_node->str = strdup(str);
	if (!new_node->str && str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->num = num;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}
/**
 * add_node_end - adds a command line at the end
 * @head: address
 * @str: string
 * Return: Always null
 */
void add_node_end(list_t **head, char *str)
{
	int num;
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
	{
		return (NULL);
	}
	new_node->str = strdup(str);
	if (!new_node->str && str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->num = num;
	new_node->next = NULL;

	if (*head)
	{
		list_t *current = *head;

		while (current->next)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}
/**
 * print_list_str - print linked list
 * @head: address
 * Return: Always 1
 */
void print_list_str(list_t *head)
{
	while (head)
	{
		printf("%s\n", head->str ? head->str : "(nil)");
		head = head->next;
	}
}
/**
 * delete_node_at_index - delete nodes
 * @head: address
 * @index: structure
 * Return: Always 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current = *head;
	list_t *previous = NULL;
	unsigned int i = 0;

	while (current && i < index)
	{
		previous = current;
		current = current->next;
		i++;
	}
	if (i == index && current)
	{
		if (previous)
		{
			previous->next = current->next;
		}
		else
		{
			*head = current->next;
		}
		free(current->str);
		free(current);
		return (1);
	}
	return (0);
}
/**
 * free_list - function to print list
 * @head: structure
 * Return: Always true
 */
void free_list(list_t **head)
{
	list_t *current = *head;

	while (current)
	{
		list_t *next = current->next;

		free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}
