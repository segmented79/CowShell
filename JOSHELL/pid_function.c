#include "main.h"

/**
 * pid_function - Entry point for the shell program.
 * @argv: list of command line arguments.
 * Return: 0 on success.
 */

void pid_function(char **args)
{
	pid_t pid;
	int status;

	/* Fork a child process to run the command */
	pid = fork();

	if (pid < 0)
	{
		/* Error occurred */
		write(STDERR_FILENO, "Fork failed\n", 12);
		free_mallocd(args);
		exit(1);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) < 0)
		{
		write(STDERR_FILENO, "Error executing command\n", 24);
		free_mallocd(args);
		exit(1);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}
