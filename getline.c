#include "main.h"
#define READ_BUF_SIZE 1024
/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @x: address of len var
 * Return: Always read byte
 */
int input_buffer(info_t *info, char **buffer, size_t *x)
{
	if (info->buffer)
	{
		*buffer = info->buffer;
		*x = strlen(info->buffer);
		info->buffer = NULL;
		return (*x);
	}
	*buffer = NULL;
	*x = 0;
	ssize_t r = getline(buffer, x, stdin);

	if (r == -1)
	{
		return (-1);
	}
	if ((*buffer)[*x - 1] == '\n')
	{
		(*buffer)[*x - 1] = '\0';
		(*x)--;
	}
	char *comment_pos = strchr(*buffer, '#');

	if (comment_pos)
	{
		*comment_pos = '\0';
		*x = comment_pos - *buffer;
	}
	return (*x);
}
/**
 * get_input - gets a line minus the newline
 * @info: parameter structure
 * @command: Addressfor buffer
 * Return: Always byte
 */
int get_input(info_t *info, char **command)
{
	char *buffer;
	size_t buffer_len;
	int buffer_type = info->buffer_type;
	int len = input_buffer(info, &buffer, &buffer_len);

	if (len == -1)
	{
		return (-1);
	}
	if (len == 0)
	{
		return (0);
	}
	if (buffer_type != 0)
	{
		if ((buffer_type == 1 && len > 2 && buffer[len - 2] == '&' &&
					buffer[len - 3] == '&') || (buffer_type == 2 &&
						len > 2 && buffer[len - 2] == '|' &&
						buffer[len - 3] == '|'))
		{
			buffer[len - 3] = '\0';
			len -= 3;
		}
		else
		{
			info->buffer_type = 0;
		}
	}
	*command = buffer;
	return (len);
}
/**
 * read_buffer- reads a buffer
 * @fd: parameter struct
 * @buffer: buffer
 * @i: size
 * Return: r
 */
int read_buffer(int fd, char *buffer, size_t *i)
{
	if (*i > 0)
	{
		return (0);
	}
	ssize_t r = read(fd, buffer, READ_BUF_SIZE);

	if (r <= 0)
	{
		return (r);
	}
	*i = r;
	return (r);
}
/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(int sig_num)
{
	printf("\n$ ");
	fflush(stdout);
}
