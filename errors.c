#include "shell.h"




/**
 * _putsfd - prints an input string
 * @string: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int fd)
{
    int i = 0;

    if (!string)
        return (0);
    while (*string)
    {
        i += _putfd(*string++, fd);
    }
    return (i);
}

/**
 * _putfd - writes the character c to given fd
 * @charr: The character to print
 * @file: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char charr, int file)
{
    static int j;
    static char buffer[WRITE_BUF_SIZE];

    if (charr == BUF_FLUSH || j >= WRITE_BUF_SIZE)
    {
        write(file, buffer, j);
        j = 0;
    }
    if (charr != BUF_FLUSH)
        buffer[j++] = charr;
    return (1);
}


/**
 * _eputchar - writes the character c to stderr
 * @charr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char charr)
{
    static int j;
    static char buffer[WRITE_BUF_SIZE];

    if (charr == BUF_FLUSH || j >= WRITE_BUF_SIZE)
    {
        write(2, buffer, j);
        j = 0;
    }
    if (charr != BUF_FLUSH)
        buffer[j++] = charr;
    return (1);
}
/**
 * _eputs - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
    int j = 0;

    if (!string)
        return;
    while (string[j] != '\0')
    {
        _eputchar(string[j]);
        j++;
    }
}

