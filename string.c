#include "shell.h"


/**
 * _strcat - concatenates two strings
 * @d: the destination buffer
 * @s: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *d, char *s)
{
    char *ret = d;

    while (*d)
        d++;
    while (*s)
        *d++ = *s++;
    *d = *s;
    return (ret);
}
/**
 * starts_with - checks if dle starts with stack
 * @stack: string to search
 * @dle: the substring to find
 *
 * Return: address of next char of stack or NULL
 */
char *starts_with(const char *stack, const char *dle)
{
    while (*dle)
        if (*dle++ != *stack++){
            return (NULL);}
    return ((char *)stack);
}

/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *string)
{
    int ij = 0;

    if (!string)
        return (0);

    while (*string++)
        ij++;
    return (ij);
}


/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    if (*str1 == *str2){
        return (0);}
    else{
        return (*str1 < *str2 ? -1 : 1);
    }}
