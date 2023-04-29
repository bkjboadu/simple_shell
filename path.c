#include "main.h"
/**
 * _pathbuilt - function id a file is executable
 * @info: structure
 * @path: path
 * Return: Always 1
 */
int _pathbuilt(info_t *info, char *path)
{
	struct stat st;

	if (!path || stat(path, &st) == -1)
		return (0);
	return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}
/**
 * find_path - finds path
 * @info: structure
 * @pathstr: path string
 * @index: path to find
 * Return: always null
 */
char *find_path(info_t *info, char *pathstr, char *index)
{
	if (!pathstr || !index)
		return (NULL);
	if (index[0] == '/')
		return (_pathbuilt(info, index) ? strdup(index) : NULL);
	char *path_copy = strdup(pathstr);
	char *path = strtok(path_copy, ":");

	while (path != NULL)
	{
		char *full_path = malloc(strlen(path) + strlen(index) + 2);

		sprintf(full_path, "%s/%s", path, index);

		if (_pathbuilt(info, full_path))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		path = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
