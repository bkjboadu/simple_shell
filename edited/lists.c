#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!head || !new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = (list_t *) malloc(sizeof(list_t));
	list_t *current_node = *head;
	size_t i;

	if (!head)
		return (NULL);

	if (!new_node)
		return (NULL);

	new_node->str = NULL;
	new_node->num = num;
	new_node->next = NULL;
	if (str)
	{
		size_t str_len = strlen(str);

		new_node->str = (char *) malloc(strlen(str) + 1);

		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
		for (i = 0; i <= str_len; i++)
			new_node->str[i] = str[i];
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	} else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node = *head, *prev_node = NULL;
	unsigned int i;
	
	for (i = 0; node && i < index; i++)
	{
		prev_node = node;
		node = node->next;
	}
	
	if (!node)
		return (0);
	
	if (!prev_node)
	{
		*head = node->next;
	} else 
	{
		prev_node->next = node->next;
	}
	
	free(node->str);
	free(node);
	
	return (1);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node;

	for (node = *head_ptr; node; node = next_node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
	}
	
	*head_ptr = NULL;
}
