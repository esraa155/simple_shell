#include "shell.h"


/**
 * free_info - frees info_t struct fields
 * @infooo: struct address
 * @allll: true if freeing all fields
 */
void free_info(info_t *infooo, int allll)
{
    ffree(infooo->argv);
    infooo->argv = NULL;
    infooo->path = NULL;
    if (allll)
    {
        if (!infooo->cmd_buf)
            free(infooo->arg);
        if (infooo->env)
            free_list(&(infooo->env));
        if (infooo->history)
            free_list(&(infooo->history));
        if (infooo->alias)
            free_list(&(infooo->alias));
        ffree(infooo->environ);
        infooo->environ = NULL;
        bfree((void **)infooo->cmd_buf);
        if (infooo->readfd > 2)
            close(infooo->readfd);
        _putchar(BUF_FLUSH);
    }
}

/**
 * set_info - initializes info_t struct
 * @infooo: struct address
 * @v: argument vector
 */
void set_info(info_t *infooo, char **v)
{
    int ij = 0;

    infooo->fname = v[0];
    if (infooo->arg)
    {
        infooo->argv = strtow(infooo->arg, " \t");
        if (!infooo->argv)
        {
            infooo->argv = malloc(sizeof(char *) * 2);
            if (infooo->argv)
            {
                infooo->argv[0] = _strdup(infooo->arg);
                infooo->argv[1] = NULL;
            }
        }
        for (ij = 0; infooo->argv && infooo->argv[ij]; ij++)
            ;
        infooo->argc = ij;

        replace_alias(infooo);
        replace_vars(infooo);
    }
}


/**
 * clear_info - initializes info_t struct
 * @infooo: struct address
 */
void clear_info(info_t *infooo)
{
    infooo->arg = NULL;
    infooo->argv = NULL;
    infooo->path = NULL;
    infooo->argc = 0;
}
