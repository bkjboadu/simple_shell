#include "main.h"
/**
 * _strcpy - string copy
 * @dest: destinatiom
 * @src: source
 * Return: Always 1
 */
char *_strcpy(char *dest, char *src)
{
	char *result = dest;

	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (result);
}
/**
 * _strdup - string duplicate
 * @str: string
 * Return: Always 1
 */
char *_strdup(const char *str)
{
	if (!str)
		return (NULL);
	int len = 0;
	const char *p = str;

	while (*p++)
		len++;
	char *new_str = malloc(len + 1);

	if (!new_str)
		return (NULL);
	_strcpy(new_str, (char *)str);
	return (new_str);
}
/**
 * shellputs - shell print function
 * @str: string
 * Return: Always 1
 */
void shellputs(char *str)
{
	while (*str)
		_eputchar(*str++);
}
/**
 * shellputchar - shell print character
 * @c: character
 * Return: Always 1
 */
int shellputchar(char c)
{
	static char buffer[1024];
	static int pos;

	if (c == '\n' || pos == 1023)
	{
		buffer[pos] = '\n';
		pos++;
		write(1, buffer, pos);
		pos = 0;
	}
	else
	{
		buffer[pos] = c;
		pos++;
	}
	return (1);
}
