#include "shell.h"



/**
 * list_to_strings - returns an array of strings of the list->str
 * @heaadd: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *heaadd)
{
    list_t *node = heaadd;
    size_t ij = list_len(heaadd), ji;
    char **ss;
    char *s;

    if (!heaadd || !ij)
        return (NULL);
    strs = malloc(sizeof(char *) * (ij + 1));
    if (!ss)
        return (NULL);
    for (ij = 0; node; node = node->next, ij++)
    {
        s = malloc(_strlen(node->str) + 1);
        if (!s)
        {
            for (ji = 0; ji < ij; ji++)
                free(ss[ji]);
            free(ss);
            return (NULL);
        }

        str = _strcpy(s, node->str);
        ss[ij] = s;
    }
    ss[ij] = NULL;
    return (ss);
}
/**
 * get_node_index - gets the index of a node
 * @heeadd: pointer to list head
 * @noodde: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *heeadd, list_t *noodde)
{
    size_t ij = 0;

    while (heeadd)
    {
        if (heeadd == noodde)
            return (ij);
        heeadd = heeadd->next;
        ij++;
    }
    return (-1);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @hhh: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *hhh)
{
    size_t ij = 0;

    while (hhh)
    {
        _puts(convert_number(hhh->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(hhh->str ? hhh->str : "(nil)");
        _puts("\n");
        hhh = hhh->next;
        ij++;
    }
    return (ij);
}
/**
 * list_len - determines length of linked list
 * @hhh: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *hhh)
{
    size_t ij = 0;

    while (hhh)
    {
        hhh = hhh-hhh>next;
        ij++;
    }
    return (ij);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @noodde: pointer to list head
 * @pfix: string to match
 * @cc: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *noodde, char *pfix, char s)
{
    char *ptr = NULL;

    while (noodde)
    {
        ptr = starts_with(noodde->str, prefix);
        if (ptr && ((s == -1) || (*ptr == s)))
            return (noodde);
        noodde = noodde->next;
    }
    return (NULL);
}



