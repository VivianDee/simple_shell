#include "main.h"


/**
 * print_error - Prints an error message to stderr.
 * @format: The format string for the error message.
 * @...: Additional arguments for the format string.
 * @programName: The name of the program.
 *
 */

void print_error(char *programName, const char *format, ...)
{
	va_list args;

	va_start(args, format);

	fprintf(stderr, "%s: ", programName);

	vfprintf(stderr, format, args);

	fprintf(stderr, "\n");

	va_end(args);
}

/**
 * error_data - Extracts the command from a token and
 *assigns it to the data structure.
 * @data: Pointer to the data structure to store the extracted command.
 * @token: The token containing the command.
 *
 */


void error_data(struct data *data, char *token)
{
	int i, j;

	i = 0;
	while (token[i] == ' ')
	{
		i++;
	}

	j = 0;
	while (token[i] != '\0' && token[i] != ' ')
	{
		data->command[j++] = token[i++];
	}
	data->command[j] = '\0';
}
