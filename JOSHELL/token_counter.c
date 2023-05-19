#include "main.h"

/**
 * token_counter - tokenizes the arguments into commands.
 * @num_args: number of arguments
 * @args: arguments
 * @command: command string
 * Return: number of arguments
 */

int token_counter(char *command, int num_args)
{
	char *token = NULL;
	token = strtok(command, " \n");
	while (token != NULL)
	{
		num_args++;
		token = strtok(NULL, " \n");
	}
	num_args++;
	return (num_args);
}
