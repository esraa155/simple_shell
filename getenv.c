#include "shell.h"


/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infooo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *infooo, char *v, char *val)
{
    char *buffer = NULL;
    list_t *node;
    char *p;

    if (!v || !val)
        return (0);

    buffer = malloc(_strlen(v) + _strlen(val) + 2);
    if (!buffer)
        return (1);
    _strcpy(buffer, v);
    _strcat(buffer, "=");
    _strcat(buffer, val);
    node = infooo->env;
    while (node)
    {
        p = starts_with(node->str, v);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buffer;
            infooo->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(infooo->env), buffer, 0);
    free(buffer);
    infooo->env_changed = 1;
    return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @infooo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int _unsetenv(info_t *infooo, char *v)
{
    list_t *node = infooo->env;
    size_t ij = 0;
    char *ptr;

    if (!node || !v)
        return (0);

    while (node)
    {
        ptr = starts_with(node->str, v);
        if (ptr && *ptr == '=')
        {
            infooo->env_changed = delete_node_at_index(&(infooo->env), ij);
            ij = 0;
            node = infooo->env;
            continue;
        }
        node = node->next;
        ij++;
    }
    return (infooo->env_changed);
}

/**
 * get_environ - returns the string array copy of our environ
 * @infooo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *infooo)
{
    if (!infooo->environ || infooo->env_changed)
    {
        infooo->environ = list_to_strings(infooo->env);
        infooo->env_changed = 0;
    }

    return (infooo->environ);
}
