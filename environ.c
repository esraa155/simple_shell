#include "shell.h"

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infooo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *infooo)
{
    if (infooo->argc != 3)
    {
        _eputs("Incorrect number of arguements\n");
        return (1);
    }
    if (_setenv(infooo, infooo->argv[1], infooo->argv[2]))
        return (0);
    return (1);
}



/**
 * _myenv - prints the current environment
 * @infooo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *infooo)
{
    print_list_str(infooo->env);
    return (0);
}



/**
 * populate_env_list - populates env linked list
 * @infooo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *infooo)
{
    list_t *node = NULL;
    size_t j;

    for (j = 0; environ[j]; j++)
        add_node_end(&node, environ[j], 0);
    infooo->env = node;
    return (0);
}
/**
 * _myunsetenv - Remove an environment variable
 * @infooo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *infooo)
{


    if (infooo->argc == 1)
    {
        _eputs("Too few arguements.\n");
        return (1);
    }
    for ( int j = 1; j <= infooo->argc; j++)
        _unsetenv(infooo, infooo->argv[j]);

    return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @infooo: Structure containing potential arguments. Used to maintain
 * @fullname: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *infooo, const char *fullname)
{
    list_t *node = infooo->env;
    char *put;

    while (node)
    {
        put = starts_with(node->str, fullname);
        if (put && *put)
            return (put);
        node = node->next;
    }
    return (NULL);
}

