#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *home_dir = _getenv(info, "HOME");
	size_t path_len = _strlen(home_dir) + _strlen("/") + _strlen(HIST_FILE) + 1;
	char *path = malloc(path_len);

	if (!home_dir)
		return (NULL);

	if (!path)
		return (NULL);

	_strcpy(path, home_dir);
	_strcat(path, "/");
	_strcat(path, HIST_FILE);

	return (path);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	list_t *node = info->history;

	if (!filename)
		return (-1);

	free(filename);
	if (fd == -1)
		return (-1);

	while (node)
	{
		ssize_t bytes_written = write(fd, node->str, strlen(node->str));

		if (bytes_written == -1)
		{
			close(fd);
			return (-1);
		}
		write(fd, "\n", 1);
		node = node->next;
	}

	write(fd, "\0", 1);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
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
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}



/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	int i = 0;
	list_t *node = info->history;

	if (!info)
		return (-1);

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	info->histcount = i;
	return (i);
}
