#include "shell.h"



/**
 * check_chain - checks we should continue chaining based on last status
 * @inffoo: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buffer
 * @ij: starting position in buffer
 * @l: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *inffoo, char *buffer, size_t *ptr, size_t ij, size_t l)
{
    size_t ji = *ptr;

    if (inffoo->cmd_buf_type == CMD_AND)
    {
        if (inffoo->status)
        {
            buffer[ij] = 0;
            ji = l;
        }
    }
    if (inffoo->cmd_buf_type == CMD_OR)
    {
        if (!inffoo->status)
        {
            buffer[ij] = 0;
            ji = l;
        }
    }

    *ptr = ji;
}


/**
 * replace_string - replaces string
 * @ol: address of old string
 * @ne: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **ol, char *ne)
{
    free(*ol);
    *ol = ne;
    return (1);
}
/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inffoo: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inffoo, char *buffer, size_t *ptr)
{
    size_t ji = *ptr;

    if (buffer[ji] == '|' && buffer[ji + 1] == '|')
    {
        buffer[ji] = 0;
        ji++;
        inffoo->cmd_buf_type = CMD_OR;
    }
    else if (buffer[ji] == '&' && buffer[ji + 1] == '&')
    {
        buffer[ji] = 0;
        ji++;
        inffoo->cmd_buf_type = CMD_AND;
    }
    else if (buffer[ji] == ';') /* found end of this command */
    {
        buffer[ji] = 0; /* replace semicolon with null */
        inffoo->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *ptr = ji;
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @infofo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *infofo)
{
    int ij = 0;
    list_t *nodee;

    for (ij = 0; infofo->argv[ij]; ij++)
    {
        if (infofo->argv[ij][0] != '$' || !infofo->argv[ij][1])
            continue;

        if (!_strcmp(infofo->argv[ij], "$?"))
        {
            replace_string(&(infofo->argv[ij]),
                           _strdup(convert_number(infofo->status, 10, 0)));
            continue;
        }
        if (!_strcmp(infofo->argv[ij], "$$"))
        {
            replace_string(&(infofo->argv[ij]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        nodee = node_starts_with(infofo->env, &infofo->argv[ij][1], '=');
        if (nodee)
        {
            replace_string(&(infofo->argv[ij]),
                           _strdup(_strchr(nodee->str, '=') + 1));
            continue;
        }
        replace_string(&infofo->argv[ij], _strdup(""));

    }
    return (0);
}
/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inffoo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *inffoo)
{
    int ij;
    list_t *nodeeeeee;
    char *ptr;

    for (ij = 0; ij < 10; ij++)
    {
        nodeeeeee = node_starts_with(inffoo->alias, inffoo->argv[0], '=');
        if (!nodeeeeee)
            return (0);
        free(inffoo->argv[0]);
        ptr = _strchr(nodeeeeee->str, '=');
        if (!ptr)
            return (0);
        ptr = _strdup(ptr + 1);
        if (!ptr)
            return (0);
        inffoo->argv[0] = ptr;
    }
    return (1);
}

