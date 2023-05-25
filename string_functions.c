#include "main.h"
/**
 *_memcpy - copies a string to another memory location
 *@dest: Is the destination which we are copying to
 *@src: Is the source from where the copying is done
 *@n: Is the number of byte being copied to destination
 *Return: Void
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;
	size_t i;

	if (dest == NULL || src == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
	{
		d[i] = s[i];
	}

	return (dest);
}
/**
 *_strdup - copies a string to another memory location
 *@src: Is the source from which the copying is done
 *Return: pointer the new location of the string
 */
char *_strdup(const char *source)
{
	char *destination;
	int length, i;

	if (source == NULL)
		return (NULL);

	length = 0;
	while (source[length] != '\0')
		length++;

	destination = (char *)malloc((length + 1) * sizeof(char));
	if (destination == NULL)
		return (NULL);

	for (i = 0; i <= length; i++)
		destination[i] = source[i];

	return (destination);
}


size_t _strlen(const char *str)
{
	size_t len = 0;

	if (str == NULL)
		return (0);

	while (str[len] != '\0')
		len++;

	return (len);
}

char *_strstr(const char *haystack, const char *needle)
{
	int i, j, k;

	for (i = 0; haystack[i] != '\0'; i++)
	{
		if (haystack[i] == needle[0])
		{
			k = i;

			for (j = 0; needle[j] != '\0'; j++)
			{
				if (haystack[k] != needle[j])
					break;

				k++;
			}

			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
	}

	return (NULL);
}


int _strcmp(const char *str1, const char *str2)
{
	int i, j;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] == str2[0])
		{
			for (j = 1; str2[j] != '\0'; j++)
			{
				if (str1[i + j] != str2[j])
					break;
			}

			if (str2[j] == '\0')
				return (0);
		}
	}

	return (-1);
}
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}
