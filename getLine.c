#include "shell.h"
/**
 * sigintHandler - blocks ctrl-C
 * @sig: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}


/**
 * get_input - gets a line minus the newline
 * @infooo: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *infooo)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t ij, ji, l;
    ssize_t rr = 0;
    char **buffer_p = &(infooo->arg), *ptr;

    _putchar(BUF_FLUSH);
    rr = input_buf(infooo, &buffer, &l);
    if (rr == -1) /* EOF */
        return (-1);
    if (l) /* we have commands left in the chain buffer */
    {
        ji = ij; /* init new iterator to current buf position */
        ptr = buffer + ij; /* get pointer for return */

        check_chain(infooo, buffer, &ji, ij, l);
        while (ji < l) /* iterate to semicolon or end */
        {
            if (is_chain(infooo, buffer, &ji))
                break;
            ji++;
        }

        ij = ji + 1; /* increment past nulled ';'' */
        if (ij >= l) /* reached end of buffer? */
        {
            ij = l = 0; /* reset position and length */
            infooo->cmd_buf_type = CMD_NORM;
        }

        *buffer_p = ptr; /* pass back pointer to current command position */
        return (_strlen(ptr)); /* return length of current command */
    }

    *buffer_p = buffer; /* else not a chain, pass back buffer from _getline() */
    return (rr); /* return length of buffer from _getline() */
}


/**
 * _getline - gets the next line of input from STDIN
 * @infooo: parameter struct
 * @p: address of pointer to buffer, preallocated or NULL
 * @l: size of preallocated ptr buffer if not NULL
 *
 * Return: str
 */
int _getline(info_t *infooo, char **p, size_t *l)
{
    static char buffer[READ_BUF_SIZE];
    static size_t ij, lenn;
    size_t kk;
    ssize_t rr = 0, str = 0;
    char *pt = NULL, *new_p = NULL, *cc;

    pt = *p;
    if (pt && l)
        str = *l;
    if (ij == lenn)
        ij = lenn = 0;

    rr = read_buf(infooo, buffer, &lenn);
    if (rr == -1 || (rr == 0 && lenn == 0))
        return (-1);

    cc = _strchr(buffer + ij, '\n');
    kk = cc ? 1 + (unsigned int)(cc - buffer) : lenn;
    new_p = _realloc(pt, str, str ? str + kk : kk + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (str)
        _strncat(new_p, buffer + ij, kk - ij);
    else
        _strncpy(new_p, buffer + ij, kk - ij + 1);

    str += kk - ij;
    ij = kk;
    pt = new_p;

    if (l)
        *l = str;
    *p = pt;
    return (str);
}

/**
 * read_buf - reads a buffer
 * @infooo: parameter struct
 * @buffer: buffer
 * @ij: size
 *
 * Return: rr
 */
ssize_t read_buf(info_t *infooo, char *buffer, size_t *ij)
{
    ssize_t rr = 0;

    if (*ij)
        return (0);
    rr = read(infooo->readfd, buffer, READ_BUF_SIZE);
    if (rr >= 0)
        *ij = rr;
    return (rr);
}




/**
 * input_buf - buffers chained commands
 * @infooo: parameter struct
 * @buffer: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *infooo, char **buffer, size_t *l)
{
    ssize_t rr = 0;
    size_t l_p = 0;

    if (!*l) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        rr = getline(buf, &len_p, stdin);
#else
        rr = _getline(infooo, buffer, &l_p);
#endif
        if (rr > 0)
        {
            if ((*buffer)[rr - 1] == '\n')
            {
                (*buffer)[rr - 1] = '\0'; /* remove trailing newline */
                rr--;
            }
            infooo->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(infooo, *buffer, infooo->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *l = rr;
                infooo->cmd_buf = buffer;
            }
        }
    }
    return (rr);
}
