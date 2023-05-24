#include "main.h"

/**
 *remove_comments - Takes care of the # operator and makes
 *it comment out anything after it.
 *@parameters: Is the command line args
 *Return: void
 */
void remove_comments(char *parameters[])
{
	int i;

	for (i = 0; parameters[i] != NULL; i++)
	{
		if (strstr(parameters[i], "#") != NULL)
			parameters[i] = NULL;
	}
}
