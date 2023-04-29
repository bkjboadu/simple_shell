#include "shell.h"

/**
 * interactive - verify if in interactive mode
 * @info: struct details
 *
 * Return: 1 if True, 0 otherwise
 */
int interactive(info_t *info)
{
	int result = 0;
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
	{
		result = 1;
	}
	return result;
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to verify
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	int result = 0;
	while (*delim != '\0')
	{
		if (*delim == c)
		{
			result = 1;
			break;
		}
		delim++;
	}
	return result;
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	int result = 0;
	while (1)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			result = 1;
			break;
		}
		else
		{
			break;
		}
	}
	return result;
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int i = 0, sign = 1, flag = 0, output = 0;
	unsigned int result = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
		i++;
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return output;
}
