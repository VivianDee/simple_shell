#include "main.h"
/**
  * check_command - Screen the command line input for logical
  *operators and parses them accordingly
  * @input: This is the string read from command line
  * @programName: The name of the program.
  *
  * Return: Void
  */
int check_command(char *input, char *programName)
{
	char *input_copy = input, *delimiters[] = {"&&", "||", ";", NULL};
	char *parameters[LETTERS], *logicalOps[LETTERS], *token;
	int isbuiltin = 0, it_exists = 0, status = 0, background = 0;
	int count = 0, i = 0, k = 0, len = -1;
	struct data data = {"\0"};

	for (k = 0; k < LETTERS; k++)
	{
		logicalOps[k] = NULL;
		parameters[k] = NULL;
	}
	check_exit(input);
	remove_leading_spaces(input);
	remove_trailing_spaces(input);
	for (k = 0; delimiters[k] != NULL; k++)
		if (_strstr(input, delimiters[k]) != NULL)
			remove_spaces_around_delimiter(input, delimiters[i]);
	count = countDelimiter(input_copy, delimiters, logicalOps);
	token = _strtok2_strings(input_copy, delimiters);
	while (token != NULL)
	{
		error_data(&data, token);
		background = command_buffer(token, parameters, &len);
		isbuiltin = check_builtin(parameters, input);
		if (!isbuiltin)
			status += (it_exists = command_exists(parameters, programName, &data));
		if (count >= 0 && i > 0)
		{
			if ((_strstr(logicalOps[i - 1], "&&") != NULL) && status != 1)
				status = 0;
			else if ((_strstr(logicalOps[i - 1], "||") != NULL) && status == 1)
				status = 0;
		}
		if (!isbuiltin && it_exists && status)
		{
			status = execute_command(parameters, background, programName, &data);
		}
		token = _strtok2_strings(NULL, delimiters);
		count--;
		i++;
		free_parameter_array(parameters);
	}
	free(input);
	return (status);
}

/**
 * command_exists - Check if the binary file for the requested command exists
 * @parameters: is the unit of arguments received from the from the input
 * @programName: The name of the program.
 * @data: A structure to save the command.
 *
 * Return: 1 on success
 */
int command_exists(char *parameters[], char *programName, struct data *data)
{
	struct stat buffer;

	if (stat(parameters[0], &buffer) == 0)
	{
		return (1);
	}
	else if (execve(parameters[0], parameters, NULL) < 0)
	{
		print_error(programName, "%s: %s", data->command, strerror(errno));
		_setenv("LASTEXITCODE", "127", 1);
		return (0);
	}
	return (1);
}

/**
 *check_builtin - This checks for whether the requested command
 *shell builtin command.
 *@input: Is the actual input by user before splitting occurs
 *@parameters: is the refined strings from the user's input
 *Return: 1 or 0 depending on the condition of whether a command
 *is builtin or not
 */
int check_builtin(char *parameters[], char *input)
{
	int exit_code = 0;

	/*This part takes care of execution of builtin commands*/
	if (parameters[0] && _strcmp(parameters[0], "#") == 0)
		return (1);
	remove_comments(parameters);
	if (parameters[0] && _strcmp(parameters[0], "exit") == 0)
	{
		if (atoi(parameters[1]))
		{
			exit_code = atoi(parameters[1]);
			_setenv("LASTEXITCODE", parameters[1], 1);
			free_parameter_array(environ);
			free_parameter_array(parameters);
			free(input);
			exit(exit_code);
		}
		else if (!parameters[1])
		{
			free_parameter_array(parameters);
			free_parameter_array(environ);
			free(input);
			exit(0);
		}
	}
	if (parameters[0] && _strcmp(parameters[0], "cd") == 0)
	{
		change_directory(parameters);
		return (1);
	}
	if (_strcmp(parameters[0], "echo") == 0)
	{
		if (parameters[1] == NULL)
		{
			_setenv("LASTEXITCODE", "0", 1);
			putchar('\n');
			return (1);
		}
		if (_strstr(parameters[1], "$") != NULL)
			return (echo_command(parameters));
	}
	return (0);
}

/**
 *command_buffer - This is the function where the parsing of the command
 *line takes place
 *@input: The user input string is held by this variable
 *@parameter: storage of the split string is inside the parameters
 *@len: Is the length of the given string given as input
 *Return: true if the process is backgroud or false foreground process
 */
int command_buffer(char *input, char *parameter[], int *len)
{
	int i = 0, background = 0;
	char path[100];

	/*Split string into token and populates the parameter buf*/
	parameter[i] = _strtok(input, " \n\t\r");
	while (parameter[i] != NULL)
	{
		parameter[i] = _strdup(parameter[i]);
		i++;
		parameter[i] = _strtok(NULL, " \n");
	}
	parameter[i] = NULL;

	if (i == 0)
		return (1);
	*len = i;

	/*Checks for buiilt-in command, call the right function and return*/
	if (_strstr(parameter[0], "exit") != NULL)
	{
		background = 1;
		return (background);
	}
	background = *parameter[i - 1] == '&';
	if (background != 0)
	{
		parameter[i - 1] = NULL;
	}
	if (_strstr(parameter[0], "cd") != NULL)
	{
		background = 1;
		return (background);
	}
	if (_strstr(parameter[0], "/") == NULL)
	{
		snprintf(path, sizeof(path), "/bin/%s", parameter[0]);
		free(parameter[0]);
		parameter[0] = _strdup(path);
	}
	return (background);
}

/**
 *free_parameter_array - deallocates all memory usage by the input string
 *@parameter: This is the pointer to array of string that must be freed
 *Return: Void
 */
void free_parameter_array(char *parameter[])
{
	int i;

	/*This frees all spaces allocated for parameter*/
	for (i = 0; parameter[i] != NULL; i++)
	{
		free(parameter[i]);
		parameter[i] = NULL;
	}
}
