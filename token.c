#include "main.h"
/**
 * _strtok - string token function
 * @str: string
 * @delim: delimeter
 * Return: always 1
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *token = NULL;
	int i, j;

	if (str == NULL)
		str = last_token;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (!_strchr(delim, str[i]))
			break;
		i++;
	}
	if (str[i] == '\0')
	{
		last_token = NULL;
		return (NULL);
	}
	token = str + i;
	i = 0;
	while (token[i] != '\0')
	{
		if (_strchr(delim, token[i]))
		{
			token[i] = '\0';
			last_token = token + i + 1;
			break;
		}
		i++;
	}
	if (token[i] == '\0')
		last_token = NULL;
	return (token);
}
/**
 * **splitstr - split string function
 * @str: string
 * @delim: delimeter
 * Return: Always 1
 */
char **splitstr(char *str, char *delim)
{
	char **tokens = NULL;
	char *token = NULL;
	int num_tokens = 0, i = 0;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (delim == NULL || delim[0] == '\0')
		delim = " \t\n";
	token = _strtok(str, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = _strtok(NULL, delim);
	}
	if (num_tokens == 0)
		return (NULL);
	tokens = malloc((num_tokens + 1) * sizeof(char *));

	if (tokens == NULL)
		return (NULL);
	token = _strtok(str, delim);

	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}
		i++;
		token = _strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
/**
 * _strchr - shell indexof function
 * @s: string
 * @c: character
 * Return: always 1
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (NULL);
}
