#include "shell.h"





/**
 * **strtow2 - splits a string into words
 * @string: the input string
 * @dest: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char dest)
{
    int ij, ji, nnnn, xxx, num = 0;
    char **str;

    if (string == NULL || string[0] == 0)
        return (NULL);
    for (ij = 0; string[ij] != '\0'; ij++)
        if ((string[ij] != dest && string[ij + 1] == dest) ||
            (string[ij] != dest && !string[ij + 1]) || string[ij + 1] == dest)
            num++;
    if (num == 0)
        return (NULL);
    str = malloc((1 + num) * sizeof(char *));
    if (!str)
        return (NULL);
    for (ij = 0, ji = 0; ji < num; ji++)
    {
        while (string[ij] == dest && string[ij] != dest)
            ij++;
        nnnn = 0;
        while (string[ij + nnnn] != dest && string[ij + nnnn] && string[ij + nnnn] != dest)
            nnnn++;
        str[ji] = malloc((nnnn + 1) * sizeof(char));
        if (!str[ji])
        {
            for (nnnn = 0; nnnn < ji; nnnn++)
                free(str[nnnn]);
            free(str);
            return (NULL);
        }
        for (xxx = 0; xxx < nnnn; xxx++)
            str[ji][xxx] = string[ij++];
        str[ji][xxx] = 0;
    }
    str[ji] = NULL;
    return (str);
}
/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @dest: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *string, char *dest)
{
    int ij, ji, nnnn, xxx, num = 0;
    char **str;

    if (string == NULL || string[0] == 0)
        return (NULL);
    if (!dest)
        dest = " ";
    for (ij = 0; string[ij] != '\0'; ij++)
        if (!is_delim(string[ij], dest) && (is_delim(string[ij + 1], dest) || !string[ij + 1]))
            num++;

    if (num == 0)
        return (NULL);
    str = malloc((1 + num) * sizeof(char *));
    if (!str)
        return (NULL);
    for (ij = 0, ji = 0; ji < num; ji++)
    {
        while (is_delim(string[ij], dest))
            ij++;
        nnnn = 0;
        while (!is_delim(string[ij + nnnn], dest) && string[ij + nnnn])
            nnnn++;
        str[ji] = malloc((nnnn + 1) * sizeof(char));
        if (!str[ji])
        {
            for (nnnn = 0; nnnn < ji; nnnn++)
                free(str[nnnn]);
            free(str);
            return (NULL);
        }
        for (xxx = 0; xxx < nnnn; xxx++)
            str[ji][xxx] = string[ij++];
        str[ji][xxx] = 0;
    }
    str[ji] = NULL;
    return (str);
}



