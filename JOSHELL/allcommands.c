#include "main.h"

/**
 * all_commands - Entry point for the shell commands.
 * @argv: list of command line arguments.
 * @args: List of commands
 * @env: Envirnment variables
 * Return:
 */
void all_commands(char **args, char **env)
{
		if (strcmp(args[0], "exit") == 0)
			exit_shell(args, 0);
		else if (strcmp(args[0], "env") == 0)
			env_function(args, env);
		else if (strcmp(args[0], "cd") == 0)
			cd_function(args);
		else
			pid_function(args);

		free_mallocd(args);
}