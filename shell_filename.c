#include "main.h"
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define BUF_FLUSH "\n"
/**
 * get_history_file - gets the history file
 * @info: structure
 * Return: Always string
 */
char *get_history_file(info_t *info)
{
	char *dir = get_environ("HOME");

	if (!dir)
		return (NULL);
	char *buf = malloc(strlen(dir) + strlen(HIST_FILE) + 2);

	if (!buf)
		return (NULL);
	sprintf(buf, "%s/%s", dir, HIST_FILE);
	return (buf);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: structure
 * Return: Always 1
 */
int write_history(info_t *info)
{
	int fd = -1;
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	list_t *node = info->history;

	while (node)
	{
		dprintf(fd, "%s\n", node->str);
		node = node->next;
	}
	dprintf(fd, "%s", BUF_FLUSH);
	close(fd);
	return (1);
}
/**
 * read_history - reads history from file
 * @info: structure
 * Return: Always 1
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
		return (0);
	int fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	char *buf = NULL;
	struct stat st;

	if (fstat(fd, &st) == -1 || st.st_size < 2)
		return (0);
	buf = malloc(st.st_size + 1);
	if (!buf)
		return (0);
	ssize_t rdlen = read(fd, buf, st.st_size);
	close(fd);
	if (rdlen <= 0)
	{
		free(buf);
		return (0);
	}
	buf[rdlen] = '\0';
	int linecount = 0;
	char *ptr = buf, *end = buf + rdlen;

	while (ptr < end)
	{
		char *nl = strchr(ptr, '\n');
		if (!nl)
			break;
		*nl = '\0';
		list_t *node = malloc(sizeof(list_t));
		if (!node)
			break;
		node->str = strdup(ptr);
		if (!node)
		{
			free(node);
			break;
		}
		node->num = linecount++;
		node->next = info->history;
		info->history = node;
		ptr = nl + 1;
	}
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
		renumber_history(info);
		return (info->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (-1);
	new_node->str = strdup(buf);
	if (!new_node->str)
	{
		free(new_node);
		return (-1);
	}
	new_node->num = linecount;
	new_node->next = NULL;
	if (!info->history)
	{
		info->history = new_node;
	}
	else
	{
		list_t *curr_node = info->history;
		while (curr_node->next)
			curr_node = curr_node->next;
		curr_node->next = new_node;
	}
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure
 * Return: histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
