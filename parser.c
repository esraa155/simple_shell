#include "shell.h"


/**
 * find_path - finds this cmd in the PATH string
 * @invfvo: the info struct
 * @pstring: the PATH string
 * @cd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *invfvo, char *pstring, char *cd)
{
    int ij = 0, pos = 0;
    char *path;

    if (!pstring)
        return (NULL);
    if ((_strlen(cd) > 2) && starts_with(cd, "./"))
    {
        if (is_cmd(invfvo, cd))
            return (cd);
    }
    while (1)
    {
        if (!pstring[ij] || pstring[ij] == ':')
        {
            path = dup_chars(pstring, pos, ij);
            if (!*path)
                _strcat(path, cd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cd);
            }
            if (is_cmd(invfvo, path))
                return (path);
            if (!pstring[ij])
                break;
            pos = ij;
        }
        ij++;
    }
    return (NULL);
}

/**
 * dup_chars - duplicates characters
 * @pstring: the PATH string
 * @st: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pstring, int st, int end)
{
    static char bufffer[1024];
    int i = 0, n = 0;

    for (n = 0, i = st; i < end; i++)
        if (pstring[i] != ':')
            bufffer[n++] = pstring[i];
    bufffer[n] = 0;
    return (bufffer);
}


/**
 * is_cmd - determines if a file is an executable command
 * @innnfooo: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *innnfooo, char *p)
{
    struct stat string;

    (void)innnfooo;
    if (!p || stat(p, &string))
        return (0);

    if (string.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}
