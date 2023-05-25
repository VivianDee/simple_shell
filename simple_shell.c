#include "main.h"
#include <signal.h>

/**
 *handle_sig - Handles the signal interrupt signal
 *@signo: Is the signal number received by the process
 *Return: Void
 */
void handle_sig(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 2);
	write(STDOUT_FILENO, "[VT~#] ", 8);
	fflush(stdout);
}
/**
 *main - This is where the ultimate read-while loop occurs
 *it prints the prompt each time and also ensures the input
 *get displayed one at a time with the help of fflush
 *@ac: is the number of argument
 *@av: is the argument vector-string input by user
 *Return: 0 on success
 */
int main(int ac, char *av[])
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read_chars;
	int status = 0;

	ac = ac;

	signal(SIGINT, handle_sig);

	while (1)
	{
		if (isatty(fileno(stdin)))
		{
			printf("[VT~#] ");
			fflush(stdout);
		}
		read_chars = _getline(&input, &len, stdin);
		if (read_chars <= 0)
		{
			if (!isatty(fileno(stdin)))
			{
				free(input);
				exit(0);
			}
			perror("_getline");
			free(input);
			return (-1);
		}
		if (feof(stdin))
		{
			fflush(stdout);
			exit(0);
		}
		input = _strtok(input, "\n");
		status = check_command(input, av[0]);
		fflush(stdout);
		fflush(stdout);
	}

	exit(status);
}
