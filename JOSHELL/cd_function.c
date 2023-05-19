#include "main.h"

/**
 * cd_function - defines the argc and argv functions
 * @argv: argument vectors
 * Return: 0
 **/

void cd_function(char **argv)
{
	if (strcmp(argv[0], "cd") == 0)
	{
		/* If the command is "cd", change the current directory */
		char *new_dir;

		if (argv[1] == NULL || strcmp(argv[1], "~") == 0)
		{
			new_dir = getenv("HOME");
		}
		else if (strcmp(argv[1], "-") == 0)
		{
			new_dir = getenv("OLDPWD");
		}
		else
		{
			new_dir = argv[1];
		}
		if (chdir(new_dir) != 0)
		{
			write(STDERR_FILENO, "Error changing directory\n", 25);
		}
		else
		{
			char *current_dir = getcwd(NULL, 0);

			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", current_dir, 1);
			free(current_dir);
		}
	}
}
