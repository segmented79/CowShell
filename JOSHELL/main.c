#include "main.h"

/**
 * main - Entry point for the shell program
 * @argc: number of arguments
 * @argv: list of command line arguments
 * Return: 0 on success
 */

int main(int argc, char **argv, char **env)
{
	char *command = NULL, **args = NULL, *command_copy = NULL;
	size_t command_size = 0;
	int exit_status = 0, num_args = 0;
	ssize_t command_length;

	while (1)
	{
		/* Print the prompt */
		print_prompt();

		/* Read the command */
		command_length = getline(&command, &command_size, stdin);
		if (command_length == -1)
		{
			/* Error or end of input */
			return (-1);
		}
		(void)argc;

		/* Parse the command into arguments */
		command_copy = strdup(command);
		num_args = token_counter(command, num_args);
		args = token_parser(command_copy, num_args);

		/* If the command is "exit", exit the shell with the given status code */
		
		exit_shell(args, exit_status);
		env_function(args);

		cd_function(argv);

		pid_function(argv);

		free(command_copy);
		free(argv);
	}
	free(command);

	return (0);
}
