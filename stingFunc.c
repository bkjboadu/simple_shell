#include "main.h"
/**
 * _strlen - string length function
 * @s: string
 * Return: always 1
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s++)
		len++;
	return (len);
}
/**
 * _strcmp - compare string
 * @s1: the first string
 * @s2: the second string
 * Return: Always 1
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/**
 * starts - function to start haystack
 * @haystack: string to search
 * @subs: substring
 * Return: always true
 */
char *starts(const char *haystack, const char *subs)
{
	while (*subs != '\0')
	{
		if (*haystack != *subs)
			return (NULL);
		haystack++;
		subs++;
	}
	return ((char *)haystack);
}
/**
 * _strcat - concatenates two strings
 * @dest: destination
 * @src: source
 * Return: always 1
 */
char *_strcat(char *dest, char *src)
{
	char *temp = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (temp);
}
