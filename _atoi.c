#include "shell.h"



/**
 * is_delim - checks if character is a delimeter
 * @charr: the char to check
 * @D: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char charr, char *D)
{
    while (*D)
        if (*D++ == charr)
            return (1);
    return (0);
}


/**
 * interactive - returns true if shell is interactive mode
 * @infooo: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *infooo)
{
    return (isatty(STDIN_FILENO) && infooo->readfd <= 2);
}
/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
    int i, sign = 1, f = 0, output;
    unsigned int result = 0;

    for (i = 0;  str[i] != '\0' && f != 2; i++)
    {
        if (str[i] == '-')
            sign *= -1;

        if (str[i] >= '0' && str[i] <= '9')
        {
            f = 1;
            result *= 10;
            result += (str[i] - '0');
        }
        else if (f == 1)
            f = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

