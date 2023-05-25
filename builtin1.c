#include "shell.h"


/**
 * print_alias -  this prints an alias string in the code
 * @node: alias node
 *
 * Return: on success 0, 1 on error
 */
int print_alias(list_t *nodeee)
{
    char *quer = NULL, *bull = NULL;

    if (nodeee)
    {
        quer = _strchr(nodeee->str, '=');
        for (bull = nodeee->string; bull<= quer; bull++)
            _putchar(*bull);
        _putchar('\'');
        _puts(quer + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}


/**
 * set_alias - this code  sets alias to string
 * @infooo: this is the parameter structure
 * @string: string alias
 *
 * Return: on success 0, on error 1
 */
int set_alias(info_t *infooo, char *string)
{
    char *quer;

    p = _strchr(string, '=');
    if (!quer)
        return (1);
    if (!*++quer)
        return (unset_alias(infooo, string));

    unset_alias(infooo, string);
    return (add_node_end(&(infooo->alias), string, 0) == NULL);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @infooo:  this struct containing potential arguments.for  constant function prototype.
 *  Return: 0 always
 */
int _myhistory(info_t *infooo)
{
    print_list(infooo->history);
    return (0);
}


/**
 * _myalias - mimics the alias builtin (man alias)
 * @infooo: the structure containing arguments.  to maintain function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *infooo)
{
    int i = 0;
    char *quer = NULL;
    list_t *nodeee = NULL;

    if (infooo->argc == 1)
    {
        nodeee = infooo->alias;
        while (nodeee)
        {
            print_alias(nodeee);
            nodeee = nodeee->next;
        }
        return (0);
    }
    for (i = 1; infooo->argv[i]; i++)
    {
        quer = _strchr(infooo->argv[i], '=');
        if (quer)
            set_alias(infooo, infooo->argv[i]);
        else
            print_alias(node_starts_with(infooo->alias, infooo->argv[i], '='));
    }

    return (0);
}
/**
 * unset_alias - sets alias to string
 * @infooo: the  parameter structure
 * @string:  string alias
 *
 * Return: success 0,  error 1.
 */
int unset_alias(info_t *infooo, char *string)
{
    char *quer, str;
    int retlu;

    quer = _strchr(string, '=');
    if (!quer)
        return (1);
    str= *quer;
    * quer= 0;
    retlu = delete_node_at_index(&(infooo->alias),
                               get_node_index(infooo->alias, node_starts_with(infooo->alias, string, -1)));
    *quer = str;
    return (retlu);
}

