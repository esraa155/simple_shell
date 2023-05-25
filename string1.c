#include "shell.h"


/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
    int l = 0;
    char *ans;

    if (string == NULL)
        return (NULL);
    while (*string++)
        l++;
    ans = malloc(sizeof(char) * (l + 1));
    if (!ans)
        return (NULL);
    for (l++; l--;)
        ans[l] = *--string;
    return (ans);
}

/**
 * _putchar - writes the character charr to stdout
 * @charr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char charr)
{
    static int ij;
    static char buffer[WRITE_BUF_SIZE];

    if (charr == BUF_FLUSH || ij >= WRITE_BUF_SIZE)
    {
        write(1, buffer, ij);
        ij = 0;
    }
    if (charr != BUF_FLUSH)
        buffer[ij++] = charr;
    return (1);
}


/**
 * _strcpy - copies a string
 * @d: the destination
 * @s: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *d, char *s)
{
    int ij = 0;

    if (d == s || s == 0)
        return (d);
    while (s[ij])
    {
        d[ij] = s[ij];
        ij++;
    }
    d[ij] = 0;
    return (d);
}


/**
 * _puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
    int ij = 0;

    if (!string)
        return;
    while (string[ij] != '\0')
    {
        _putchar(string[ij]);
        ij++;
    }
}


