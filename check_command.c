#include "main.h"




void check_command(char *input)
{
	char *input_copy = strdup(input), *delimiters[] = {"&&", "||", ";", NULL}, error_no[10];
	char *parameters[LETTERS], *logicalOps[LETTERS], *token;
	int isbuiltin = 0, it_exists = 0, status = 0, background = 0, count = 0, i = 0;

	if (strstr(input, "&&") != NULL)
		remove_spaces_around_delimiter(input_copy, "&&");
	if (strstr(input, "||") != NULL)
		remove_spaces_around_delimiter(input_copy, "||");
	if (strstr(input, ";") != NULL)
		remove_spaces_around_delimiter(input_copy, ";");

	count = countDelimiter(input_copy, delimiters, logicalOps);

	token = _strtok2_strings(input_copy, delimiters);
	while (token != NULL)
	{
		background = command_buffer(token, parameters);
		isbuiltin = check_builtin(parameters);
		if (!isbuiltin)
			it_exists = command_exists(parameters);

		status += it_exists;

		if (count >= 0 && i > 0)
		{
			if ((strstr(logicalOps[i - 1], "&&") != NULL) && status != 1)
				status = 0;
			else if ((strstr(logicalOps[i - 1], "||") != NULL) && status == 1)
				status = 0;
		}

		if (!isbuiltin && it_exists && status)
		{
			status = execute_command(parameters, background);
			sprintf(error_no, "%d", status);
			setenv("LASTEXITCODE", error_no, 1);
		}

		token = _strtok2_strings(NULL, delimiters);
		count--;
		i++;
	}
}

int command_exists(char *parameters[])
{
	struct stat buffer;

	if (stat(parameters[0], &buffer) == 0)
	{
		return (1);
	}
	else if (execve(parameters[0], parameters, NULL) < 0)
	{
		perror("execve");
		setenv("LASTEXITCODE", "127", 1);
		return (0);
	}

	return (1);
}

int check_builtin(char *parameters[])
{
	int exit_code = 0;

	remove_comments(parameters);
	if (parameters[0] && strstr(parameters[0], "exit") != NULL)
	{
		if (parameters[1])
		{
			exit_code = atoi(parameters[1]);
			setenv("LASTEXITCODE", parameters[1], 1);
			exit(exit_code);
		}
		else
			exit(0);
	}
	if (parameters[0] && strstr(parameters[0], "cd") != NULL)
	{
		change_directory(parameters);
		return (1);
	}
	if (strstr(parameters[0], "echo") != NULL)
	{
		if (parameters[1] == NULL)
		{
			setenv("LASTEXITCODE", "0", 1);
			putchar('\n');
			return (1);
		}
		if (strstr(parameters[1], "$") != NULL)
			return (echo_command(parameters));
	}

	return (0);
}

int command_buffer(char *input, char *parameter[])
{
	int i = 0, background = 0;
	char path[100];

	parameter[i] = _strtok(input, " \n\t\r");
	while (parameter[i] != NULL)
	{
		parameter[i] = strdup(parameter[i]);
		i++;
		parameter[i] = _strtok(NULL, " \n");
	}
	parameter[i] = NULL;

	if (i == 0)
		return (1);

	if (strstr(parameter[0], "exit") != NULL)
	{
		background = 1;
		return (background);
	}

	if ((background = *parameter[i - 1] == '&') != 0)
	{
		parameter[i - 1] = NULL;
	}
	if (strstr(parameter[0], "cd") != NULL)
	{
		background = 1;
		return (background);
	}
	if (strstr(parameter[0], "/") == NULL)
	{
		snprintf(path, sizeof(path), "/bin/%s", parameter[0]);
		free(parameter[0]);
		parameter[0] = strdup(path);
	}

	return (background);
}
