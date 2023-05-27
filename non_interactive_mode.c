#include "main.h"

/**
 *_strchr - Locates a character in a string
 *@str: The string to search
 *@c: The character to locate
 *Return: position of the character in the string*
 */
char *_strchr(const char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 *replaceChar - Replaces a character in a string
 *@str: The string to modify
 *Return: Void
 */
void replaceChar(char *str)
{
	char *ptr = _strchr(str, '\n');

	while (ptr != NULL)
	{
		*ptr = ';';
		ptr = _strchr(ptr, '\n');
	}
}
