#include "shell.h"

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inffffo: the parameter & return inffffo struct
 *
 * Return: void
 */
void fork_cmd(info_t *inffffo)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(inffffo->path, inffffo->argv, get_environ(inffffo)) == -1)
        {
            free_info(inffffo, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(inffffo->status));
        if (WIFEXITED(inffffo->status))
        {
            inffffo->status = WEXITSTATUS(inffffo->status);
            if (inffffo->status == 126)
                print_error(inffffo, "Permission denied\n");
        }
    }
}

/**
 * find_builtin - finds a builtin command
 * @inffffo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *inffffo)

{
    int ij, ret = -1;
    builtin_table builtintbl[] = {
            {"exit", _myexit},
            {"env", _myenv},
            {"help", _myhelp},
            {"history", _myhistory},
            {"setenv", _mysetenv},
            {"unsetenv", _myunsetenv},
            {"cd", _mycd},
            {"alias", _myalias},
            {NULL, NULL}
    };

    for (ij = 0; builtintbl[ij].type; ij++)
        if (_strcmp(inffffo->argv[0], builtintbl[ij].type) == 0)
        {
            inffffo->line_count++;
            ret = builtintbl[ij].func(inffffo);
            break;
        }
    return (ret);
}


/**
 * hsh - main shell loop
 * @inffoo: the parameter & return info struct
 * @aaave: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *inffoo, char **aaave)
{
    ssize_t nnn = 0;
    int ret = 0;


    while (nnn != -1 && ret != -2)
    {
        clear_info(inffoo);
        if (interactive(inffoo))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        nnn = get_input(inffoo);
        if (nnn != -1)
        {
            set_info(inffoo, aaave);
            ret = find_builtin(inffoo);
            if (ret == -1)
                find_cmd(inffoo);
        }
        else if (interactive(inffoo))
            _putchar('\n');
        free_info(inffoo, 0);
    }
    write_history(inffoo);
    free_info(inffoo, 1);
    if (!interactive(inffoo) && inffoo->status)
        exit(inffoo->status);
    if (ret == -2)
    {
        if (inffoo->err_num == -1)
            exit(inffoo->status);
        exit(inffoo->err_num);
    }
    return (ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inffffo: the parameter & return info struct
 *
 * Return: void
 */
 
void find_cmd(info_t *inffffo)
{
    
    char *p = NULL;
    int ij, aaa;

    inffffo->p = inffffo->argv[0];
    if (inffffo->linecount_flag == 1)
    {
        inffffo->line_count++;
        inffffo->linecount_flag = 0;
    }
    for (ij = 0, aaa = 0; inffffo->arg[ij]; ij++)
        if (!is_delim(inffffo->arg[ij], " \t\n"))
            aaa++;
    if (!aaa)
        return;

    p = find_path(inffffo, _getenv(inffffo, "PATH="), inffffo->argv[0]);
    if (p)
    {
        inffffo->p = p;
        fork_cmd(inffffo);
    }
    else
    {
        if ((interactive(inffffo) || _getenv(inffffo, "PATH=")
             || inffffo->argv[0][0] == '/') && is_cmd(inffffo, inffffo->argv[0]))
            fork_cmd(inffffo);
        else if (*(inffffo->arg) != '\n')
        {
            inffffo->status = 127;
            print_error(inffffo, "not found\n");
        }
    }
}



