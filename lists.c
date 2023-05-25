#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @headd: address of pointer to head node
 * @string: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **headd, const char *string, int n)
{
    list_t *new_head;

    if (!headd)
        return (NULL);
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);
    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = n;
    if (string)
    {
        new_head->str = _strdup(string);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }
    new_head->next = *headd;
    *headd = new_head;
    return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @headd: address of pointer to head node
 * @string: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **headd, const char *string, int n)
{
    list_t *new_node, *node;

    if (!headd)
        return (NULL);

    node = *headd;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = n;
    if (string)
    {
        new_node->str = _strdup(string);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *headd = new_node;
    return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @hhh: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *hhh)
{
    size_t ij = 0;

    while (hhh)
    {
        _puts(hhh->str ? hhh->str : "(nil)");
        _puts("\n");
        hhh = hhh->next;
        ij++;
    }
    return (ij);
}
/**
 * free_list - frees all nodes of a list
 * @headd_p: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **headd_p)
{
    list_t *node, *next_node, *head;

    if (!headd_p || !*headd_p)
        return;
    headd = *headd_p;
    node = headd;
    while (node)
    {
        next_node = node->next;
        free(node->string);
        free(node);
        node = next_node;
    }
    *headd_p = NULL;
}

/**
 * delete_node_at_index - deletes node at given index
 * @headd: address of pointer to first node
 * @in: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **headd, unsigned int in)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!headd || !*headd)
        return (0);

    if (!in)
    {
        node = *headd;
        *headd = (*headd)->next;
        free(node->str);
        free(node);
        return (1);
    }
    node = *headd;
    while (node)
    {
        if (i == in)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return (0);
}



