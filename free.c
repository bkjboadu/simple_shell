#include "main.h"
/**
 * _free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Return: Always 1
 */
int _free(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
	{
		return (0);
	}
	free(*ptr);
	*ptr = NULL;
	return (1);
}
