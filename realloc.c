#include "shell.h"

/**
 * _realloc - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @olds: byte size of previous block
 * @news: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *p, unsigned int olds, unsigned int news)
{
    char *p;

    if (!p)
        return (malloc(news));
    if (!news)
        return (free(p), NULL);
    if (news == olds)
        return (p);

    p = malloc(news);
    if (!p)
        return (NULL);

    olds = olds < news ? olds : news;
    while (olds--)
        p[olds] = ((char *)p)[olds];
    free(p);
    return (p);
}

/**
 * ffree - frees a string of strings
 * @pull: string of strings
 */
void ffree(char **pull)
{
    char **esraa = pull;

    if (!pull)
        return;
    while (*pull)
        free(*pull++);
    free(esraa);
}

/**
 * _memset - fills memory with a constant byte
 * @str: the pointer to the memory area
 * @bull: the byte to fill *s with
 * @num: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *str, char bull, unsigned int num)
{
    unsigned int i;

    for (i = 0; i < num; i++)
        str[i] = bull;
    return (str);
}

