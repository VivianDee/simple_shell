#include "main.h"

/**
 *remove_comments - Takes care of the # operator and makes
 *it comment out anything after it.
 *@parameters: Is the command line args
 *Return: void
 */

void remove_comments(char *parameters[])
{
	int i = 0, len = 0;

	while (parameters[i] != NULL)
	{
		len++;
		i++;
	}

	for (i = 0; i < len; i++)
	{
		if (_strstr(parameters[i], "#") != NULL)
		{
			free(parameters[i]);
			parameters[i] = NULL;
			while (i <= len)
			{
				free(parameters[i]);
				parameters[i] = NULL;
				i++;
			}
		}
	}
}
