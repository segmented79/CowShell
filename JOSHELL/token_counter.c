#include "main.h"

/**
 * token_counter - tokenizes the arguments into commands.
 * @command: command string
 * Return: number of arguments
 */

int token_counter(char *command)
{
	int num_args = 0;
	char *token = NULL;

	token = strtok(command, " \n");
	while (token != NULL)
	{
		num_args++;
		token = strtok(NULL, " \n");
	}
	free(command);
	return (num_args);
}
