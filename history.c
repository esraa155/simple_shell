#include "shell.h"



/**
 * renumber_history - renumbers the history linked list after changes
 * @infooo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *infooo)
{
    list_t *node = infooo->history;
    int ij = 0;

    while (node)
    {
        node->num = ij++;
        node = node->next;
    }
    return (infooo->histcount = ij);
}
/**
 * build_history_list - adds entry to a history linked list
 * @infooo: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lin: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *infooo, char *buffer, int lin)
{
    list_t *node = NULL;

    if (infooo->history)
        node = infooo->history;
    add_node_end(&node, buffer, lin);

    if (!infooo->history)
        infooo->history = node;
    return (0);
}

/**
 * get_history_file - gets the history file
 * @infooo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *infooo)
{
    char *buffer, *dirc;

    dirc = _getenv(infooo, "HOME=");
    if (!dirc)
        return (NULL);
    buffer = malloc(sizeof(char) * (_strlen(dirc) + _strlen(HIST_FILE) + 2));
    if (!buffer)
        return (NULL);
    buffer[0] = 0;
    _strcpy(buffer, dirc);
    _strcat(buffer, "/");
    _strcat(buffer, HIST_FILE);
    return (buffer);
}


/**
 * write_history - creates a file, or appends to an existing file
 * @infooo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *infooo)
{
    ssize_t file;
    char *filename = get_history_file(infooo);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    file = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (file == -1)
        return (-1);
    for (node = infooo->history; node; node = node->next)
    {
        _putsfd(node->str, file);
        _putfd('\n', file);
    }
    _putfd(BUF_FLUSH, file);
    close(file);
    return (1);
}

/**
 * read_history - reads history from file
 * @infooo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *infooo)
{
    int ij, last = 0, linecount = 0;
    ssize_t file, rd, size = 0;
    struct stat str;
    char *buf = NULL, *filename = get_history_file(infooo);

    if (!filename)
        return (0);

    file = open(filename, O_RDONLY);
    free(filename);
    if (file == -1)
        return (0);
    if (!fstat(file, &str))
        size = str.st_size;
    if (size < 2)
        return (0);
    buf = malloc(sizeof(char) * (size + 1));
    if (!buf)
        return (0);
    rd = read(file, buf, size);
    buf[size] = 0;
    if (rd <= 0)
        return (free(buf), 0);
    close(file);
    for (ij = 0; ij < size; ij++)
        if (buf[ij] == '\n')
        {
            buf[ij] = 0;
            build_history_list(infooo, buf + last, linecount++);
            last = ij + 1;
        }
    if (last != ij)
        build_history_list(infooo, buf + last, linecount++);
    free(buf);
    infooo->histcount = linecount;
    while (infooo->histcount-- >= HIST_MAX)
        delete_node_at_index(&(infooo->history), 0);
    renumber_history(infooo);
    return (infooo->histcount);
}
