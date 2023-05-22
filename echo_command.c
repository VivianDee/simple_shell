#include "main.h"

int echo_command(char *parameters[])
{
	char *copy = strdup(parameters[1]);
	char *variable = getenv(copy + 1), *last_exit_code = getenv("LASTEXITCODE");
	pid_t id = getpid();

	if (parameters[1][1] == '?' && last_exit_code)
	{
		printf("%s\n", last_exit_code);
		return (1);
	}
	else if (parameters[1][1] == '$')
	{
		printf("%d\n", id);
		setenv("LASTEXITCODE", "0", 1);
		return (1);
	}
	else if (variable)
	{
		printf("%s\n", variable);
		setenv("LASTEXITCODE", "0", 1);
		return (1);
	}
	else if (strlen(parameters[1]) > 1)
	{
		putchar('\n');
		setenv("LASTEXITCODE", "0", 1);
		return (1);
	}

	return (0);
}
