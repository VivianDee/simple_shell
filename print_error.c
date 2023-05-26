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
	const char newline = '\n', *separator = ": ";
	size_t progNameLen = 0, separatorLen = 0;
	ssize_t totalBytesWritten = 0;

	va_list args;

	va_start(args, format);

	progNameLen = _strlen(programName);
	write(STDERR_FILENO, programName, progNameLen);
	separatorLen = _strlen(separator);
	write(STDERR_FILENO, separator, separatorLen);

	_vsnprintf(format, args, &totalBytesWritten);

	write(STDERR_FILENO, &newline, 1);
	totalBytesWritten++;

	va_end(args);
}


/**
 *  _vsnprintf - Prints an string message to stderr.
 * @format: The format string for the error message.
 * @args: A va_list
 * @totalBytesWritten: Number of chars written to stderr
 *
 */
void _vsnprintf(const char *format, va_list args, ssize_t *totalBytesWritten)
{
	const char *ptr = format, *str = NULL;
	char digitChar;
	ssize_t strLen = 0, numLen = 0, tempNum = 0, divisor = 0, num = 0;

	while (*ptr != '\0')
	{
		if (*ptr == '%')
		{
			ptr++;
			if (*ptr == 's')
			{
				str = va_arg(args, const char *);
				strLen = _strlen(str);
				write(STDERR_FILENO, str, strLen);
				*totalBytesWritten += strLen;
			}
			else if (*ptr == 'd')
			{
				num = va_arg(args, int);
				tempNum = num;
				if (tempNum < 0)
				{
					write(STDERR_FILENO, "-", 1);
					*totalBytesWritten += 1;
					tempNum = -tempNum;
				}

				divisor = 1;
				while (tempNum / divisor > 9)
				{
					divisor *= 10;
				}
				while (divisor > 0)
				{
					digitChar = '0' + (tempNum / divisor);
					write(STDERR_FILENO, &digitChar, 1);
					*totalBytesWritten += 1;
					numLen += 1;
					tempNum %= divisor;
					divisor /= 10;
				}

			}
			else
			{
				write(STDERR_FILENO, ptr - 1, 2);
				*totalBytesWritten += 2;
			}
		}
		else
		{
			write(STDERR_FILENO, ptr, 1);
			(*totalBytesWritten)++;
		}
		ptr++;
	}
}

/**
 * error_data - Extracts the command from a token and assigns it.
 *
 * @data: Pointer to the data structure to store the extracted command.
 * @token: The token containing the command.
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
