#include "main.h"

/**
 * print_prompt - prints to the shell
 *
 * Return: 0
 */

void print_prompt(void)
{
	char *current_dir = getcwd(NULL, 0);

	write(STDOUT_FILENO, current_dir, strlen(current_dir));
	write(STDOUT_FILENO, " $ ", 3);
	free(current_dir);
}
