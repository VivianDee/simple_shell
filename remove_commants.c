#include "main.h"


void remove_comments(char *parameters[])
{
	int i;

	for (i = 0; parameters[i] != NULL; i++)
	{
		if (strstr(parameters[i], "#") != NULL)
			parameters[i] = NULL;
	}
}
