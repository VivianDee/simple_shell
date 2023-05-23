#include "main.h"
/**
 *execute_command - This function is where forking and exec'ing
 *of a child process takes place depending on the type of job
 *@parameters: Is the command options/argument being parsed
 *@background: The return value for background process check
 *to acertain the type of job a process is
 *Return: 1 on success
 */
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
