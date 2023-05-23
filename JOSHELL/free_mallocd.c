#include "main.h"

/**
 * free_mallocd - Exit the shell program if the user enters "exit"
 * @args: list of command line arguments
 * Return: If user enters "exit", return the exit status. Otherwise, return 0.
 */

void free_mallocd(char **args)
{
	int idx = 0;

	if (args == NULL)
		return;

	while (args[idx])
	{
		free(args[idx]);
		idx++;
	}
}
