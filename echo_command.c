#include "main.h"

/**
 *echo_command - This is responsible for getting the
 *exit status of previous command and parent pid when echo $?
 *or echo $$ is run
 *@parameters: Is the command line arguments array
 *Return: 0 on success
 */
int echo_command(char *parameters[])
{
	char *variable = _getenv(parameters[1] + 1);
	char *last_exit_code = _getenv("LASTEXITCODE");
	pid_t id = getpid();

	if (parameters[1][1] == '?' && last_exit_code)
	{
		printf("%s\n", last_exit_code);
		return (1);
	}
	else if (parameters[1][1] == '$')
	{
		printf("%d\n", id);
		_setenv("LASTEXITCODE", "0", 1);
		return (1);
	}
	else if (variable)
	{
		printf("%s\n", variable);
		_setenv("LASTEXITCODE", "0", 1);
		return (1);
	}
	else if (_strlen(parameters[1]) > 1)
	{
		putchar('\n');
		_setenv("LASTEXITCODE", "0", 1);
		return (1);
	}

	return (0);
}
