#include "main.h"

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
