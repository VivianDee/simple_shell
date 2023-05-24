#include "main.h"
/**
 *_strtok - Splits strings into its constituent parts
 *@string1: is the first string
 *@string2: is the second string
 *Return: NULL
 */
char *_strtok(char *string1, const char *string2)
{
	static char *last_token;
	unsigned int i, j;

	if (string2 == NULL || string2[0] == '\0')
	{
		return (NULL);
	}
	if (string1 == NULL)
	{
		string1 = last_token;
	}
	if (string1 != NULL && string1[0] != '\0')
	{
		last_token = string1;
		for (i = 0; i != (_strlen(string1) + 1); i++)
		{
			if (string1[i] == '\0')
			{
				last_token = NULL;
			}
			for (j = 0; string2[j] != '\0'; j++)
			{
				if (string1[i] == string2[j])
				{
					string1[i] = '\0';
					last_token = string1 + i + 1;
					break;
				}
			}
		}
		return (string1);
	}
	return (NULL);
}
/**
 *_strtok2_strings - Tokenizes string
 *@string1: Is the first string
 *@string2: Is the second string
 *Return: NULL
 */
char *_strtok2_strings(char *string1, char *string2[])
{
	static char *last_token;
	unsigned int i, j;
	const char *delimiter;
	int delimiter_length;

	if (string2 == NULL || string2[0] == NULL)
	{
		return (NULL);
	}
	if (string1 == NULL)
	{
		string1 = last_token;
	}
	if (string1 != NULL && string1[0] != '\0')
	{
		last_token = string1;
		for (i = 0; i < _strlen(string1); i++)
		{
			if (string1[i] == '\0')
			{
				last_token = NULL;
			}
			for (j = 0; string2[j] != NULL; j++)
			{
				delimiter = string2[j];
				delimiter_length = _strlen(delimiter);

				if (_strncmp(string1 + i, delimiter, delimiter_length) == 0)
				{
					string1[i] = '\0';
					last_token = string1 + i + delimiter_length;
					return (string1);
				}
			}
		}
		last_token = NULL;
		return (string1);
	}

	return (NULL);
}
