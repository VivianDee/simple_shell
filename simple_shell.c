#include "main.h"

void print_error(char *programName, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	fprintf(stderr, "%s: ", programName);

	vfprintf(stderr, format, args);

	fprintf(stderr, "\n");

	va_end(args);
}



char *_strtok(char *string1, const char *string2)
{
	static char *last_token = NULL;
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
		for (i = 0; i != (strlen(string1) + 1); i++)
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


size_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int fd = fileno(stream);
	ssize_t read_chars = 0, i;
	size_t total_chars = 0;
	char *buff = NULL, *new_buff = NULL, temp_buff[LETTERS];

	do
	{
		read_chars = read(fd, temp_buff, LETTERS);
		if (read_chars == -1)
		{
			perror("read");
			free(buff);
			return (-1);
		}

		new_buff = (char *)realloc(buff, (total_chars + read_chars + 1) * sizeof(char));
		if (new_buff == NULL)
		{
			perror("realloc");
			free(buff);
			return (-1);
		}

		buff = new_buff;
		for (i = 0; i < read_chars; i++)
		{
			buff[total_chars + i] = temp_buff[i];
		}

		total_chars += read_chars;
	} while (read_chars == LETTERS);

	buff[total_chars] = '\0';

	*lineptr = NULL;
	*lineptr = buff;
	*n = total_chars;
	return (*n);
}

void free_parameter_array(char *parameter[])
{
	int i;

	for (i = 0; parameter[i] != NULL; i++)
	{
		free(parameter[i]);
		parameter[i] = NULL;
	}
}

int command_buffer(char *input, char *parameter[], int *len)
{
	int i = 0, background = 0;
	char path[100];

	parameter[i] = strtok(input, " \n\t\r");
	while (parameter[i] != NULL)
	{
		parameter[i] = strdup(parameter[i]);
		i++;
		parameter[i] = strtok(NULL, " \n");
	}
	parameter[i] = NULL;

	if (i == 0)
		return (1);
	*len = i;

	if (strstr(parameter[0], "exit") != NULL)
	{
		background = 1;
		return (background);
	}

	if ((background = *parameter[i - 1] == '&') != 0)
	{
		parameter[i - 1] = NULL;
	}
	if (strstr(parameter[0], "cd") != NULL)
	{
		background = 1;
		return (background);
	}
	if (strstr(parameter[0], "/") == NULL)
	{
		snprintf(path, sizeof(path), "/bin/%s", parameter[0]);
		free(parameter[0]);
		parameter[0] = strdup(path);
	}

	return (background);
}


int execute_command(char *parameters[], int background, char *programName)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
		    {
			    execve(parameters[0], parameters, environ);
			    print_error(programName, "%s: %s", parameters[0], strerror(errno));
			    exit(0);
		    }
	else if (pid > 0)
	{
		if (!background)
		{
			waitpid(pid, &status, 0);
			return (WEXITSTATUS(status));
		}
	}
	else
	{
		perror("Fork");
		return (0);
	}
	return (1);
}

void check_command(char *input, char *programName)
{
	char error_no[10];
	char *parameters[LETTERS];
	int background = 0, len = 0, status = 0;

	background = command_buffer(input, parameters, &len);
	status = execute_command(parameters, background, programName);
	sprintf(error_no, "%d", status);
	free_parameter_array(parameters);
	free(input);
}

int main(int ac, char *av[])
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read_chars;

	ac = ac;

	while (1)
	{
		if (isatty(fileno(stdin)))
		{
			printf("[VT~#] ");
			fflush(stdout);
		}
		read_chars = getline(&input, &len, stdin);
		if (read_chars <= 0)
		{
			if (isatty(fileno(stdin)))
				perror("_getline");
			return (-1);
		}
		if (feof(stdin))
		{
			fflush(stdout);
			exit(0);
		}
		input = strtok(input, "\n");
		check_command(input, av[0]);
		fflush(stdout);
		fflush(stdout);
	}

	return (0);
}
