#include  "main.h"
/**
 * _strconvert - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string
 */
int _strconvert(char *s)
{
	int num = 0, sign = 1;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			num = num * 10 + (*s - '0');
			if (num < 0)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
		s++;
	}
	return (sign * num);
}
/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string
 */
void print_error(info_t *info, char *estr)
{
	fprintf(stderr, "%s: %d: %s: %s", info->fname,
			info->line_count, info->argv[0], estr);
}
/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters print
 */
int print_d(int input, int fd)
{

	int i, count = 0;
	unsigned int _abs_, current;
	char buffer[12];

	if (input < 0)
	{
		_abs_ = -input;
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	sprintf(buffer, "%u", current);
	count += strlen(buffer);
	if (input < 0)
	{
		fprintf(fd == STDERR_FILENO ? stderr : stdout, "-%s", buffer);
	}
	else
	{
		fprintf(fd == STDERR_FILENO ? stderr : stdout, "%s", buffer);
		for (i = 1000000000; i > 1; i /= 10)
		{
			if (_abs_ / i)
			{
				__putchar('0' + current / i);
				count++;
			}
			current %= i;
		}
	}
	return (count);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = "0123456789ABCDEF"[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	char *p = strchr(buf, '#');

	if (p && (p == buf || *(p - 1) == ' '))
	*p = '\0';
}
