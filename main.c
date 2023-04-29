#include "main.h"
#define INFO_INIT
/**
 * main - entry level
 * @count: count
 * @a: argunment
 * Return: Always 0
 */
int main(int count, char **a)
{
	info_t info[] = { INFO_INIT };
	int fp = 2;

	asm ("mov %1, %0\n\t" "add $3, %0" : "=r" (fp) : "r" (fp));
	if(count == 2)
	{
		fp = open(a[1], O_RDONLY);
		if (fp == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(a[0]);
				_eputs(": 0: Can't open ");
				_eputs(a[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fp;
	}
	populate_env_list(info);
	read_history(info);
	lop(info, a);
	return (EXIT_SUCCESS);
}
