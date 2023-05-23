#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGS 10

unsigned int _strlen(char *s);
void print_prompt(void);
int token_counter(char *command);
int exit_shell(char **args, int exit_status);
void env_function(char **args, char **env);
void cd_function(char **args);
char **token_parser(char *command_copy, int num_args);
void pid_function(char **args);
void all_commands(char **args, char **env);
void free_mallocd(char **args);


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
	int /*exit_status = 0, */num_args = 0;
	ssize_t command_length = 0;

	while (1)
	{
		/* Print the prompt */
		print_prompt();

		/* Read the command */
		command_length = getline(&command, &command_size, stdin);
		if (command_length == -1)
		{
			/* Error or end of input */
			free(command);
			return (-1);
		}
		(void)argc; (void)argv;

		/* Parse the command into arguments */
		command_copy = strdup(command);
		num_args = token_counter(command);
		args = token_parser(command_copy, num_args);

		/* If the command is "exit", exit the shell with the given status code */
		all_commands(args, env);
		
		/*free(command_copy);*/
		free_mallocd(args);
	}
	free(command);

	return (0);
}

#include "main.h"
/**
 * _strlen - Finds the length of a string
 * @s: The input string.
 * Return: The length of the string
 */

unsigned int _strlen(char *s)
{
	unsigned int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}

	return (len);
}

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
}

#include "main.h"

/**
 * cd_function - defines the argc and argv functions
 * @args: argument vectors
 * Return: 0
 **/

void cd_function(char **args)
{
	if (strcmp(args[0], "cd") == 0)
	{
		/* If the command is "cd", change the current directory */
		char *new_dir;

		if (args[1] == NULL || strcmp(args[1], "~") == 0)
		{
			new_dir = getenv("HOME");
		}
		else if (strcmp(args[1], "-") == 0)
		{
			new_dir = getenv("OLDPWD");
		}
		else
		{
			new_dir = args[1];
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
	free_mallocd(args);
}

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

		/* char **env = getenv();*/

		while (*env != NULL)
		{
			write(STDOUT_FILENO, *env, strlen(*env));
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	}
	free_mallocd(args);
}

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
		/*free_mallocd(args);*/
		exit (exit_status);
	}
	return (0);
}

#include "main.h"

/**
 * free_mallocd - Exit the shell program if the user enters "exit"
 * @args: list of command line arguments
 * Return: If user enters "exit", return the exit status. Otherwise, return 0.
 */

void free_mallocd(char **args)
{
	int idx = 0;

	if (args == NULL)
		return;

	while (args[idx])
	{
		free(args[idx]);
		idx++;
	}

	free(args);
}

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

#include "main.h"

/**
 * print_prompt - prints to the shell
 *
 * Return: 0
 */

void print_prompt(void)
{
	char *current_dir = getcwd(NULL, 0);

	write(STDOUT_FILENO, current_dir, strlen(current_dir));
	write(STDOUT_FILENO, " $ ", 3);
	free(current_dir);
}

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
	/*free(command);*/
	return (num_args);
}

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
		i++;
	}
	args[i] = NULL;
	free(command_copy);
	
	return (args);
}

