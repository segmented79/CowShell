#include "main.h"
/**
 * _strlen - Finds the length of a string
 * @s: The input string.
 * Return: The length of the string
 */

unsigned int _strlen(char *s)
{
	unsigned int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}

	return (len);
}