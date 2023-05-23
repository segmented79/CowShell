#include "main.h"

/**
 * exit_shell - Exit the shell program if the user enters "exit"
 * @argv: list of command line arguments
 * @exit_status: exit the shell
 * Return: If user enters "exit", return the exit status. Otherwise, return 0.
 */

int exit_shell(char **args, int exit_status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			perror("Error");
			exit_status = 1/* atoi(args[1]) */;
		}
		free_mallocd(args);
		exit (exit_status);
	}
	return (0);
}
