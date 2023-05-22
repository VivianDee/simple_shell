#include "main.h"

int execute_command(char *parameters[], int background)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(parameters[0], parameters, environ);
		perror("execve");
		exit(0);
	}
	else if (pid > 0)
	{
		if (!background)
		{
			waitpid(pid, &status, 0);
			update_pwd_in_env();
			return (WEXITSTATUS(status));
		}
	}
	else
	{
		perror("Fork");
		return (0);
	}
	return (1);
}
