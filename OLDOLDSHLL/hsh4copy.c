#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void _puts(char *s);
char *_strcat_sp(char *destin, char *source);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *_strcpy(char *destin, char *source);
unsigned int _strlen(char *s);
void _shell_prompt(void);
void _EOF_case(char *LinePtr);
char *_get_home_dir(char **env);
char *_get_oldpwd(char **env);
void _exit_shell(char **LinePtr_copy);
void _invok_child(char **LinePtr_copy, char *name, char **env, size_t prm_i);
int _strncmp(const char *s1, const char *s2, size_t n);
int _change_dir_func(char *path, char **env);
void _execmd(char **LinePtr_copy, char *name, char **env, size_t prm_i);
void _envir_print(char **env);
char **_get_pathtok(char **env);
void _error_msg(char *name, size_t prm_i, char **LinePtr_copy);
char **_parse_token(char *LinePtr, const char *delimit);
void _free_argv(char **LinePtr_copy);
void _free_before_exit(char **LinePtr_copy);
void _handle(int signals);
int main(int ac, char **av, char **env);



/**
 * main - Entry point
 * Description: A function that creates a simple shell
 * @ac: argument count
 * @av: Array of strings
 * @env: Array of environment variables
 * Return: Always 0.
 */

int main(int ac, char **av, char **env)
{
	char *LinePtr = NULL, **LinePtr_copy = NULL;
	ssize_t numchars_read = 0;
	size_t line_size = 0, prm_i = 0;

	while (1)
	{
		prm_i = prm_i + 1;
		_shell_prompt();
		/*signal(SIGINT, _handle);*/
		numchars_read = getline(&LinePtr, &line_size, stdin);
		if (numchars_read == -1)
			_EOF_case(LinePtr);
		else if (*LinePtr == '\n' || *LinePtr == ' ' )
			free(LinePtr);
		else
		{
			LinePtr[_strlen(LinePtr) - 1] = '\0';
			LinePtr_copy = _parse_token(LinePtr, " \0");
			free(LinePtr);
			if (_strcmp(LinePtr_copy[0], "exit") == 0)
				_exit_shell(LinePtr_copy);
			else if (_strcmp(LinePtr_copy[0], "cd") == 0)
				_change_dir_func(LinePtr_copy[1], env);
			else
				_invok_child(LinePtr_copy, av[0], env, prm_i);
		}
		fflush(stdin);
		LinePtr = NULL, line_size = 0;
	}
	(void)ac;
	return (EXIT_SUCCESS);
}


/**
 * _atoi - Converts a string to integer.
 * @s: Input string.
 * Return: Integer
 */

int _atoi(char *s)
{
	int i, d, n, lengthh, f, number;

	i = d = n = 0;
	lengthh = 0;
	f = 0;
	number = 0;

	while (s[lengthh] != '\0')
		lengthh++;

	while (i < lengthh && f == 0)
	{
		if (s[i] == '-')
			++d;

		if (s[i] >= '0' && s[i] <= '9')
		{
			number = s[i] - '0';
			if (d % 2)
				number = -number;
			n = n * 10 + number;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}

	if (f == 0)
		return (0);
	else
		return (n);
}



/**
 * _EOF_case - checks if EOF character was encountered
 * @LinePtr: The pointer to the input string.
 * Return: Nothing
 */

void _EOF_case(char *LinePtr)
{
	if (LinePtr)
	{
		free(LinePtr);
		LinePtr = NULL;
	}

	if (isatty(0))
		write(1, "\n", 1);

	free(LinePtr);
	exit(EXIT_SUCCESS);
}


/**
 * _puts - prints a string to stdout
 * @s: pointer
 * Return: nothing
 */
void _puts(char *s)
{
	while (*s != 0)
	{
		write(1, &(*s), 1);
		s++;
	}
}



/**
 * _strcat_sp - Concatenates two strings.
 * @destin: An input string.
 * @source: An input string.
 * Return: A pointer to the resulting string.
 */

char *_strcat_sp(char *destin, char *source)
{
	char *temp = destin;
	int i = 0, j = 0;

	while (destin[i])
	{
		i++;
	}

	destin[i] = '/';
	i++;

	while (source[j])
	{
		destin[i] = source[j];
		i++;
		j++;
	}
	return (temp);
}



/**
 * _strcmp - A funtion that compares two strings.
 * @s1: first string
 * @s2: second string
 * Return: 1 if strings are the same, 0 if not.
 */

int _strcmp(char *s1, char *s2)
{
	unsigned int i = 0;

	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}



/**
 * _strcpy - Copies a string and paste to another string.
 * @destin: string destination
 * @source: string source
 * Return: A pointer to copied string.
 */

char *_strcpy(char *destin, char *source)
{
	char *tempor = destin;
	int i = 0;

	while (source[i])
	{
		destin[i] = source[i];
		i++;
	}
	destin[i] = '\0';

	return (tempor);
}


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


/**
 * _strncmp - compates n characters in 2 strings
 * @s1: first string
 * @s2: 2nd string
 * @n: number of bytes to compare
 * Return: 0 if it's a match and -1 or 1 if not
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return ((s1[i] < s2[i]) ? -1 : 1);
		}
		else if (s1[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}



/**
 * _change_dir_func - changes working directory.
 * @path: The new current working directory.
 * @env: Array of environment variables
 * Return: 0 on success, -1 on failure.
 */

int _change_dir_func(char *path, char **env)
{
	char *new_dir, *current_dir/* *buffer = NULL */;

	if (path == NULL || _strcmp(path, "~") == 0)
		new_dir = _get_home_dir(env);
	else if (_strcmp(path, "-") == 0)
		new_dir = _get_oldpwd(env);
	else
		new_dir = path;

	if (chdir(new_dir) != 0)
		perror("Error");
	else
	{
		current_dir = getcwd(NULL, 0);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", current_dir, 1);
		if (current_dir != NULL)
			free(current_dir);
	}
	free(path);
	return (0);
}



/**
 * _envir_print - A function that prints all enviromental variables.
 * @env: The pointer to enviromental variables.
 * Return:
 */

void _envir_print(char **env)
{
	size_t l = 0, len = 0;

	while (env[l])
	{
		len = _strlen(env[l]);

		write(1, env[l], len);
		write(1, "\n", 1);

		l++;
	}
}



/**
 * _error_msg - prints error messahe
 * @name: The name of the shell.
 * @prm_i: Number of prm_i.
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * Return: Nothing.
 */

void _error_msg(char *name, size_t prm_i, char **LinePtr_copy)
{
	char c;

	c = prm_i + '0';
	write(1, name, _strlen(name));
	_puts(": ");
	write(1, &c, 1);
	_puts(": ");
	write(1, LinePtr_copy[0], _strlen(LinePtr_copy[0]));
	_puts(": not found\n");
}


/**
 * _execmd - A function that executes a LinePtr_copy.
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * @name: The name of the shell.
 * @env: The pointer to the enviromental variables.
 * @prm_i: Number of executed prm_i.
 * Return: Nothing.
 */

void _execmd(char **LinePtr_copy, char *name, char **env, size_t prm_i)
{
	char **pathvar = NULL, *fullcmdpath = NULL;
	struct stat buf;
	unsigned int i = 0;

	if (_strcmp(LinePtr_copy[0], "env") == 0)
		_envir_print(env);
	else if (stat(LinePtr_copy[0], &buf) == 0)
	{
		if (execve(LinePtr_copy[0], LinePtr_copy, env) < 0)
		{
			perror(name);
			_free_before_exit(LinePtr_copy);
		}
	}
	else
	{
		pathvar = _get_pathtok(env);
		while (pathvar[i])
		{
			fullcmdpath = _strcat_sp(pathvar[i], LinePtr_copy[0]);
			i++;
			if (stat(fullcmdpath, &buf) == 0)
			{
				if (execve(fullcmdpath, LinePtr_copy, env) < 0)
				{
					perror(name);
					_free_argv(pathvar);
					_free_before_exit(LinePtr_copy);
				}
				return;
			}
		}
		_error_msg(name, prm_i, LinePtr_copy);
		_free_argv(pathvar);
		_free_argv(LinePtr_copy);
		LinePtr_copy = NULL;
	}
}


/**
 * _exit_shell - Exits the shell if "exit" is encountered
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * Return: Nothing.
 */

void _exit_shell(char **LinePtr_copy)
{
	int sta_tus = 0;

	if (LinePtr_copy[1] == NULL)
	{
		_free_argv(LinePtr_copy);
		exit(0);
	}
	else
	{
		perror("Error");
		_free_argv(LinePtr_copy);
		return;
	}

	sta_tus = _atoi(LinePtr_copy[1]);
	_free_argv(LinePtr_copy);
	exit(sta_tus);
}


/**
 * _free_argv - frees all memory allocated for LinePtr_copy.
 * @LinePtr_copy: copy of input string
 * Return: Nothing.
 */

void _free_argv(char **LinePtr_copy)
{
	size_t j = 0;

	if (LinePtr_copy == NULL)
		return;

	while (LinePtr_copy[j])
	{
		free(LinePtr_copy[j]);
		j++;
	}

	if (LinePtr_copy[j] == NULL)
	{
		free(LinePtr_copy[j]);
	}

	free(LinePtr_copy);
}



/**
 * _free_before_exit - frees all memory allocated and exit.
 * @LinePtr_copy: copy of input string
 * Return: Nothing.
 */

void _free_before_exit(char **LinePtr_copy)
{
	size_t i = 0;

	if (LinePtr_copy == NULL)
		return;

	while (LinePtr_copy[i])
	{
		free(LinePtr_copy[i]);
		i++;
	}

	if (LinePtr_copy[i] == NULL)
	{
		free(LinePtr_copy[i]);
	}

	free(LinePtr_copy);
	exit(1);
}


/**
 * _get_home_dir - Gets the value of the
 * HOME enviromental variable.
 * @env: Array of enviromental variables.
 * Return: the path of the home dir
 */

char *_get_home_dir(char **env)
{
	char *home = NULL;
	size_t i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "HOME=", 5) == 0)
		{
			home = &env[i][5];
			break;
		}
		i++;
	}

	return (home);
}


/**
 * _get_oldpwd - Gets the value of the
 * OLDPWD enviromental variable.
 * @env: Array of enviromental variables.
 * Return: OLDPWD path
 */

char *_get_oldpwd(char **env)
{
	char *home = NULL;
	size_t i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			home = &env[i][7];
			break;
		}
		i++;
	}

	return (home);
}


/**
 * _get_pathtok - Gets the full value from the
 * PATH enviromental variable.
 * @env: Array of enviromental variables.
 * Return: the directories listed in the
 * PATH environment variable.
 */

char **_get_pathtok(char **env)
{
	char *pathvalue = NULL, **pathvar = NULL;
	size_t k = 0;

	pathvalue = strtok(env[k], "=");
	while (env[k])
	{
		if (_strcmp(pathvalue, "PATH") == 0)
		{
			pathvalue = strtok(NULL, "\n");
			pathvar = _parse_token(pathvalue, ":");
			return (pathvar);
		}
		k++;
		pathvalue = strtok(env[k], "=");
	}
	return (NULL);
}



/**
 * _handle - handle Ctr + C signal.
 * @signals: The signal to handle.
 * Return:
 */

void _handle(int signals)
{
	(void)signals;
	write(1, "RN_SHELL $ ", 11);
}


/**
 * _invok_child - makes child process
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * @name: The shell's name.
 * @env: Array of enviromental variables.
 * @prm_i: Prompt count.
 * Return: Nothing.
 */

void _invok_child(char **LinePtr_copy, char *name, char **env, size_t prm_i)
{
	pid_t pid = 0;
	int status = 0, wait_err = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		_free_before_exit(LinePtr_copy);
	}
	else if (pid == 0)
	{
		_execmd(LinePtr_copy, name, env, prm_i);
		_free_argv(LinePtr_copy);
	}
	else
	{
		wait_err = waitpid(pid, &status, 0);
		if (wait_err < 0)
		{
			_free_before_exit(LinePtr_copy);
		}
		_free_argv(LinePtr_copy);
	}
}


/**
 * _parse_token - A function that split and create a full string command.
 * @delimit: The delimiter for str.
 * @LinePtr: The pointer to input string.
 * Return: A string with full command.
 */

char **_parse_token(char *LinePtr, const char *delimit)
{
	char *token = NULL, **LinePtr_copy = NULL;
	size_t buffersize = 0;
	int i = 0;

	if (LinePtr == NULL)
		return (NULL);

	buffersize = _strlen(LinePtr);
	LinePtr_copy = malloc(sizeof(char *) * (buffersize + 1));
	if (LinePtr_copy == NULL)
	{
		perror("Unable to allocate LinePtr");
		free(LinePtr);
		_free_argv(LinePtr_copy);
		exit(EXIT_FAILURE);
	}
	token = strtok(LinePtr, delimit);
	while (token != NULL)
	{
		LinePtr_copy[i] = malloc(_strlen(token) + 1);
		if (LinePtr_copy[i] == NULL)
		{
			perror("Unable to allocate LinePtr");
			_free_argv(LinePtr_copy);
			free(LinePtr);
			return (NULL);
		}
		_strcpy(LinePtr_copy[i], token);
		token = strtok(NULL, delimit);
		i++;
	}
	LinePtr_copy[i] = NULL;
	return (LinePtr_copy);
}


/**
 * _shell_prompt - prints the prompt
 * Return: Nothing.
 */

void _shell_prompt(void)
{
	if (isatty(0))
		write(1, "RN_SHELL $ ", 11);
}
