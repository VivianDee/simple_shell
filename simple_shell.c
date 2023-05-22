#include "main.h"

int main(int ac, char **av)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read_chars;

	(void)av;

	while (1)
	{
		printf("[VT~#] ");
		fflush(stdout);
		read_chars = _getline(&input, &len, stdin);
		if (read_chars <= 0)
		{
			if(ac > 1)
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
		fflush(stdout);
		fflush(stdout);
	}

	free(input);
	return (0);
}
