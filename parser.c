#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat file_stats;

	(void)info;
	if (path == NULL || stat(path, &file_stats) != 0)
		return (0);

	return (S_ISREG(file_stats.st_mode));
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	int length = stop - start;
	int i, j = 0;
	char *result = malloc(length + 1);

	if (result == NULL)
		return (NULL);


	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			result[j++] = pathstr[i];
	}
	result[j] = '\0';

	return (result);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path, *p, *c;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			p = path;
			c = cmd;
			while (*p)
				p++;
			if (*(p - 1) != '/')
			{
				*p = '/';
				p++;
			}
			while (*c)
			{
				*p = *c;
				p++;
				c++;
			}
			*p = '\0';
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i + 1;
		}
		i++;
	}
	return (NULL);
}
