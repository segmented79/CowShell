#include "main.h"

/**
 * env_function - Entry point for the shell program.
 * @argv: list of command line arguments.
 * Return: 0 on success.
 */

void env_function(char **args, char **env)
{
	if (strcmp(args[0], "env") == 0)
	{
		/* If the command is "env", print the current environment */

		char **env = getenv();

		while (*env != NULL)
		{
			write(STDOUT_FILENO, *env, strlen(*env));
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	}
}
