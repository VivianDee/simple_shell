#include "main.h"

/**
 *main - This is where the ultimate read-while loop occurs
 *it prints the prompt each time and also ensures the input
 *get displayed one at a time with the help of fflush
 *@ac: is the number of argument
 *@av: is the argument vector-string input by user
 *Return: 0 on success
 */
int main(int ac, char **av)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read_chars;

	(void)av;
	(void)ac;

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
			if (isatty(fileno(stdin)))
			perror("_getline");
			return (-1);
		}
		if (feof(stdin))
		{
			fflush(stdout);
			exit(0);
		}
		input = _strtok(input, "\n");
		check_command(input);
		free(input);
		fflush(stdout);
		fflush(stdout);
	}

	return (0);
}
