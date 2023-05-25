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
	size_t name_length = _strlen(name);
	size_t value_length = _strlen(value);
	size_t entry_length = name_length + value_length + 2;
	char env_entry[LETTERS];
	int result = 0;

	if (name == NULL || value == NULL)
		return (-1);

	if (!overwrite && _getenv(name) != NULL)
		return (0);

	_memcpy(env_entry, name, name_length);
	env_entry[name_length] = '=';
	_memcpy(env_entry + name_length + 1, value, value_length);
	env_entry[entry_length - 1] = '\0';

	result = _putenv(env_entry);

	return (result);
}
/**
 *_getenv - gets the environment from the env array
 *@name: is the name in the variable
 *Return: NULL
 */
char *_getenv(const char *name)
{
	char **environment = NULL;
	size_t name_length = 0;

	if (name == NULL)
		return (NULL);
	name_length = _strlen(name);

	environment = environ;
	while (*environment != NULL)
	{
		if (_strcmp(*environment, name) == 0 && (*environment)[name_length] == '=')
			return (&((*environment)[name_length + 1]));
		environment++;
	}
	return (NULL);
}

/**
 *_putenv - Install an environment variable into env
 *@string: is the string as variable to be put in environ
 *Return: 0 on success
 */
int _putenv(const char *string)
{
	char *new_environ[LETTERS], **env_var = NULL;
	size_t string_length = _strlen(string), i = 0, env_count = 0;

	for (i = 0; i < LETTERS; i++)
		new_environ[i] = NULL;

	if (string == NULL || string[0] == '\0' || string_length == 0)
		return (-1);

	env_var = environ;
	while (*env_var != NULL)
	{
		if (_strcmp(*env_var, string) == 0)
		{
			*env_var = _strdup(string);
			if (*env_var == NULL)
				return (-1);
			return (0);
		}
		env_var++;
	}

	env_count = env_var - environ;

	for (i = 0; i < env_count; i++)
	{
		new_environ[i] = _strdup(environ[i]);
	}

	new_environ[env_count] = _strdup(string);

	new_environ[env_count + 1] = NULL;
	free(environ);
	environ = new_environ;

	return (0);
}
