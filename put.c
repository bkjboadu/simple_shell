#include "main.h"
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	if (!str)
		return;
	while (*str)
		_eputchar(*str++);
}
/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: Always 1
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	i = 0;
	buf[i++] = c;
	return (1);
}
/**
 * _putsfd - prints an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _putsfd(char *str, int fd)
{
	if (!str)
		return (0);
	int i = 0;

	while (*str)
		i += _putfd(*str++, fd);
	return (i);
}
/**
 * _putfd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: Always 1
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
