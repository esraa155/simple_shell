
#include "shell.h"



/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@charr: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *str, char charr)
{
    do {
        if (*str == charr)
            return (str);
    } while (*str++ != '\0');

    return (NULL);
}



/**
 **_strncpy - copies a string
 *@d: the destination string to be copied to
 *@srccc: the source string
 *@amount: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *d, char *srccc, int amount)
{
    int ij, ji;
    char *str = d;

    ij = 0;
    while (srccc[ij] != '\0' && ij < amount - 1)
    {
        d[ij] = srccc[ij];
        ij++;
    }
    if (ij < amount)
    {
        ji = ij;
        while (ji < amount)
        {
            d[ji] = '\0';
            ji++;
        }
    }
    return (str);
}

/**
 **_strncat - concatenates two strings
 *@d: the first string
 *@srccc: the second string
 *@amount: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *d, char *srccc, int amount)
{
    int ij, ji;
    char *str = d;

    ij = 0;
    ji = 0;
    while (d[ij] != '\0')
        ij++;
    while (srccc[ji] != '\0' && ji < amount)
    {
        d[ij] = srccc[ji];
        ij++;
        ji++;
    }
    if (ji < amount)
        d[ij] = '\0';
    return (str);
}



