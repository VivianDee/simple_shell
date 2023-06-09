#include "main.h"
/**
 *execute_command - This function is where forking and exec'ing
 *of a child process takes place depending on the type of job
 *@pmeters: Is the command options/argument being parsed
 *@bg: The return value for background process check
 *@programName: The name of the program.
 *@data: A structure to save the command.
 *
 *Return: 1 on success
 */
int execute_command(char *pmeters[], int bg, char *programName, data *data)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(pmeters[0], pmeters, environ);
		print_error(programName, "%s: %s", data->command, strerror(errno));
		exit(0);
	}
	else if (pid > 0)
	{
		if (!bg)
		{
			waitpid(pid, &status, 0);
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
