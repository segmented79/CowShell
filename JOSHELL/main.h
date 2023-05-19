#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGS 10

void print_prompt(void);
int token_counter(char *command, int num_args);
int exit_shell(char **args, int exit_status);
void env_function(char **args, char **env);
void cd_function(char **args);
char **token_parser(char *command_copy, int num_args);
void pid_function(char **args);


#endif
