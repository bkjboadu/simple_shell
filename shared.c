#include "main.h"
/**
 * setMem - set memory function
 * @ptr: pointer
 * @b: byte
 * @num: number
 * Return: Always 1
 */
char *setMem(char *ptr, char b, unsigned int num)
{
	char *p = ptr;

	while (num--)
	{
		*p++ = b;
	}
	return (ptr);
}
/**
 * freestr - free string functiom
 * @str: strinb of string
 * Return: Always true
 */
void freestr(char **str)
{
	if (!str)
		return;
	char *pt = str;

	while (*pt)
	{
		free(*pt);
		pt++;
	}
	free(str);
}
/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: always 1
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	char *src = ptr, *dest = new_ptr;

	for (unsigned int i = 0; i < old_size && i < new_size; i++)
		dest[i] = src[i];
	free(ptr);
	return (new_ptr);
}

