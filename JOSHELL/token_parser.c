#include "main.h"

/**
 * token_parser - parses the tokens.
 * @argv: list of command line arguments.
 * @command_copy: copies the commands
 * @num_args: number of arguments
 * Return: 0 on success
 */

char **token_parser(char *command_copy, int num_args)
{
	int i = 0;
	char **args, *token;

	args = malloc(sizeof(char *) * (num_args + 1));
	if (args == NULL)
		return (NULL);

	token = strtok(command_copy, " \n");
	while (args != NULL)
	{
		args[i] = malloc(sizeof(char) * strlen(token) + 1);
		if (args[i] == NULL)
			return (NULL);
		strcpy(args[i], token);
		token = strtok(NULL, " \n");
		i++;
	}
	args[i] = NULL;
	return (args);
}
