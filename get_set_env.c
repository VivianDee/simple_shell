#include "main.h"

int _setenv(const char *name, const char *value, int overwrite)
{
	size_t name_length = strlen(name);
	size_t value_length = strlen(value);
	size_t entry_length = name_length + value_length + 2;
	char *env_entry = NULL;
	int result = 0;

	if (name == NULL || value == NULL)
		    return (-1);

	if (!overwrite && _getenv(name) != NULL)
		return (0);

	env_entry = (char *)malloc(entry_length);
	if (env_entry == NULL)
		return (-1);

	_memcpy(env_entry, name, name_length);
	env_entry[name_length] = '=';
	_memcpy(env_entry + name_length + 1, value, value_length);
	env_entry[entry_length - 1] = '\0';

	result = _putenv(env_entry);

	if (result != 0)
		free(env_entry);

	return (result);
}

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

int _putenv(const char *string)
{
    char **new_environ = NULL, **env_var = NULL;
    size_t string_length = _strlen(string), i, j, env_count;

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
    new_environ = (char **)malloc((env_count + 2) * sizeof(char *));
    if (new_environ == NULL)
        return (-1);

    for (i = 0; i < env_count; i++)
    {
        new_environ[i] = _strdup(environ[i]);
        if (new_environ[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(new_environ[j]);
            free(new_environ);
            return (-1);
        }
    }

    new_environ[env_count] = _strdup(string);
    if (new_environ[env_count] == NULL)
    {
        for (i = 0; i < env_count; i++)
            free(new_environ[i]);
        free(new_environ);
        return (-1);
    }

    new_environ[env_count + 1] = NULL;

    environ = new_environ;

    return (0);
}
