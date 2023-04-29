#include "main.h"
/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	char* ret = dest;

	while (*src && n--)
	{
		*dest++ = *src++;
	}
	while (n--)
	{
		*dest++ = '\0';
	}
	return (ret);
}
char* my_strncat(char* dest, const char* src, size_t n)
{
	char* ret = dest;

	while (*dest) dest++;
	while (n-- && *src) *dest++ = *src++;
	*dest = '\0';
	return (ret);
}
char* my_strchr(const char* s, int c)
{
	while (*s && *s != c) s++;
	return ((*s == c) ? (char*)s : NULL);
}
