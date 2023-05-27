#include "main.h"
/**
 *remove_spaces_around_delimiter - is a function for parsing the
 *the string input, ensures the space are removed correctly
 *@delimiter: Is what defines the separator string in the input
 *@input: Is the user input on the stdin stream
 *Return: void
 */
void remove_spaces_around_delimiter(char *input, const char *delimiter)
{
	int delimiter_length = _strlen(delimiter);
	int text_length = _strlen(input);
	int i, j;
	char *space_pos;
	char *start = _strstr(input, delimiter);

	while (start != NULL)
	{
		if (start != input && *(start - 1) == ' ')
		{
			for (i = start - input - 1, j = i + 1; j <= text_length; i++, j++)
			{
				input[i] = input[j];
			}
			text_length--;
		}
		start = _strstr(start + delimiter_length, delimiter);
	}

	start = _strstr(input, delimiter);
	while (start != NULL)
	{
		space_pos = start + delimiter_length;
		while (*space_pos == ' ')
		{
			for (i = space_pos - input, j = i + 1; j <= text_length; i++, j++)
			{
				input[i] = input[j];
			}
			text_length--;
		}
		start = _strstr(start + delimiter_length, delimiter);
	}
}
/**
 *countDelimiter - It counts the number of delimeters present.
 *@input: is the user input.
 *@delimiters: This are the array options passed as delimiters.
 *@logicalOps: They are the array of logical operators given.
 *Return: the number of delimeters.
 */
int countDelimiter(char *input, char *delimiters[], char *logicalOps[])
{
	int count = 0, i;
	char *ptr = input;

	while (*ptr != '\0')
	{
		for (i = 0; delimiters[i] != NULL; i++)
		{
			if (_strncmp(ptr, delimiters[i], _strlen(delimiters[i])) == 0)
			{
				logicalOps[count] = delimiters[i];
				count++;
				break;
			}
		}
		ptr++;
	}

	return (count);
}
