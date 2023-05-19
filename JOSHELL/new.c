#include "new.h"

	void print_prompt() {
	char *prompt = "$ ";
	write(STDOUT_FILENO, prompt, strlen(prompt));
	}

	int read_command(char *command, char **arguments) {
	char input[MAX_COMMAND_LENGTH];
	fgets(input, MAX_COMMAND_LENGTH, stdin);

	// Remove the newline character from the input
	input[strlen(input) - 1] = '\0';

	// Tokenize the input into command and arguments
	char *token = strtok(input, " ");
	int i = 0;
	while (token != NULL && i < MAX_ARGUMENTS) {
		arguments[i++] = token;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL;

	// Copy the command into the command buffer
	strncpy(command, arguments[0], MAX_COMMAND_LENGTH);

	return i;
	}

	int main() {
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS + 1];

	while (1) {
		print_prompt();

		int num_arguments = read_command(command, arguments);

		if (num_arguments == 0) {
		// Empty command line, prompt again
		continue;
		}

		if (strcmp(command, "exit") == 0) {
		// Exit the shell
		break;
		}

		pid_t pid = fork();

		if (pid == -1) {
		char *error_message = "Error: fork failed.\n";
		write(STDERR_FILENO, error_message, strlen(error_message));
		continue;
		}

		if (pid == 0) {
		// Child process
		execvp(command, arguments);
		char error_message[MAX_COMMAND_LENGTH + 20];
		sprintf(error_message, "Error: could not execute command '%s'.\n", command);
		write(STDERR_FILENO, error_message, strlen(error_message));
		exit(EXIT_FAILURE);
		} else {
		// Parent process
		int status;
		waitpid(pid, &status, 0);
		}
	}

	return 0;
	}
