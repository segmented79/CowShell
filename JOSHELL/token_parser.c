#include "main.h"

/**
 * token_parser - parses the tokens.
 * @command_copy: copies the commands
 * @num_args: number of arguments
 * Return: 0 on success
 */

char **token_parser(char *command_copy, int num_args)
{
	int i = 0, toklen;
	char **args, *token;

	args = malloc(sizeof(char *) * (num_args + 1));
	if (args == NULL)
		return (NULL);
	/*args[num_args] = NULL;*/
	token = strtok(command_copy, " \n");
	while (token != NULL)
	{
		toklen = _strlen(token) + 1;
		args[i] = malloc(sizeof(char) * toklen);
		if (args[i] == NULL)
			return (NULL);
		strcpy(args[i],token);
		token = strtok(NULL, " \n");
		/*args = NULL;*/
		i++;
	}
	args[i] = NULL;
	free(command_copy);
	
	return (args);
}
