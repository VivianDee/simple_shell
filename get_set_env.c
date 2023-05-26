#include "main.h"

/**
 *_setenv - sets the environment variable
 *@name: is the name of the environment
 *@value: is the value of the set environment
 *@overwrite: it determines whether to set or unset variable
 *Return: the result of the set env.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, name_length = 0, value_length = 0, entry_length = 0;
	char new_env[LETTERS];

	name_length = _strlen(name);
	value_length = _strlen(value);
	entry_length = name_length + value_length + 2;

	_memcpy(new_env, name, name_length);
	new_env[name_length] = '=';
	_memcpy(new_env + name_length + 1, value, value_length);
	new_env[entry_length - 1] = '\0';

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strstr(environ[i], name) != NULL)
		{
			if (overwrite)
			{
				_strcpy(environ[i] + name_length + 1, value);
				return (0);
			} else
			{
				return (1);
			}
		}
	}

	if (!overwrite)
	{
		environ[i] = new_env;
		environ[i + 1] = NULL;
	}
	return (0);
}

/**
 *_getenv - gets the environment from the env array
 *@name: is the name in the variable
 *Return: NULL
 */
char *_getenv(const char *name)
{
	int i, name_length = 0;

	name_length = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_length) == 0 && environ[i][name_length] == '=')
		{
			return (environ[i] + name_length + 1);
		}
	}

	return (NULL);
}
