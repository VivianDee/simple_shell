#include "main.h"

/**
 *_strcmp - compares one string to another
 *@str1: Is the string we are comparing to
 *@str2: Is the exact string we are comparing
 *Return: 0 if the string compared is the same,
 *1 if the first is greater or -1 if the second is greater
 */
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
/**
 *_strncmp - compares a string to another
 *@s1: Is the first string we are comparing with
 *@s2: Is the string we are comparing
 *@n: Is the number of byte in the string being compared
 *Return: 0 if the number of string compare is the same
 */
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
