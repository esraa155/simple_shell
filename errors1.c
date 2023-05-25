#include "shell.h"


/**
 * convert_number - converter function, a clone of itoa
 * @numberr: number
 * @baseeeee: base
 * @f: argument flags
 *
 * Return: string
 */
char *convert_number(long int numberr, int baseeeee, int f)
{
    static char *arr;
    static char buff[50];
    char signnn = 0;
    char *p;
    unsigned long n = numberr;

    if (!(f & CONVERT_UNSIGNED) && numberr < 0)
    {
        n = -numberr;
        signnn = '-';

    }
    arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    p = &buff[49];
    *p = '\0';

    do {
        *--p = arr[n % baseeeee];
        n /= baseeeee;
    } while (n != 0);

    if (signnn)
        *--p = signnn;
    return (p);
}


/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @in: the input
 * @file: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int in, int file)
{
    int (*__putch)(char) = _putchar;
    int ij, counter = 0;
    unsigned int _ab, curr;

    if (file == STDERR_FILENO)
        __putch = _eputchar;
    if (in < 0)
    {
        _ab = -in;
        __putch('-');
        counter++;
    }
    else
        _ab = in;
    curr = _ab;
    for (ij = 1000000000; ij > 1; ij /= 10)
    {
        if (_ab / ij)
        {
            __putch('0' + curr / ij);
            counter++;
        }
        curr %= ij;
    }
    __putch('0' + curr);
    counter++;

    return (counter);
}
/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *str)
{
    int ij = 0;
    unsigned long int res = 0;

    if (*str == '+')
        str++;  /* TODO: why does this make main return 255? */
    for (ij = 0;  str[ij] != '\0'; ij++)
    {
        if (str[ij] >= '0' && str[ij] <= '9')
        {
            res *= 10;
            res += (str[ij] - '0');
            if (res > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (res);
}


/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @bufffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *bufffer)
{
    int i;

    for (i = 0; bufffer[i] != '\0'; i++)
        if (bufffer[i] == '#' && (!i || bufffer[i - 1] == ' '))
        {
            bufffer[i] = '\0';
            break;
        }
}

/**
 * print_error - prints an error message
 * @infooo: the parameter & return info struct
 * @estrrrr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *infooo, char *estrrrr)
{
    _eputs(infooo->fname);
    _eputs(": ");
    print_d(infooo->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(infooo->argv[0]);
    _eputs(": ");
    _eputs(estrrrr);
}


