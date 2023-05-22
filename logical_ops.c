#include "main.h"

void remove_spaces_around_delimiter(char *input, const char *delimiter)
{
	int delimiter_length = strlen(delimiter);
	int text_length = strlen(input);
	int i, j;
	char *space_pos;
	char *start = strstr(input, delimiter);

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
		start = strstr(start + delimiter_length, delimiter);
	}

	start = strstr(input, delimiter);
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
		start = strstr(start + delimiter_length, delimiter);
	}
}


int countDelimiter(char *input, char *delimiters[], char *logicalOps[])
{
	int count = 0, i;
	char *ptr = input;

	while (*ptr != '\0')
	{
		for (i = 0; delimiters[i] != NULL; i++)
		{
			if (strncmp(ptr, delimiters[i], strlen(delimiters[i])) == 0)
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
