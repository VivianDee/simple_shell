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
 *@source: Is the source from which the copying is done
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
/**
 *_strlen - determines the length of a string
 *@str: pointer to the string whose length is determined
 *Return: the length of the string
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	if (str == NULL)
		return (0);

	while (str[len] != '\0')
		len++;

	return (len);
}
/**
 *_strstr - Looks for the occurence of a string in an array
 *@haystack: Is the array of string
 *@needle: Is the string being searched
 *Return: pointer the new location of the string
 */
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

char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}
