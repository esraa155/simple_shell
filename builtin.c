#include "shell.h"

/**
 * _myhelp - changes the current directory of the process
 * @infooo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *infooo)
{
    char **arg_array;

    arg_array = infooo->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return (0);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
    char *str, *dirc, bufferrr[1024];
    int chdir_ret;

    str = getcwd(bufferrr, 1024);
    if (!str)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dirc = _getenv(info, "HOME=");
        if (!dirc)
            chdir_ret = /* TODO: what should this be? */
                    chdir((dirc = _getenv(info, "PWD=")) ? dirc : "/");
        else
            chdir_ret = chdir(dirc);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(str);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
                chdir((dirc = _getenv(info, "OLDPWD=")) ? dirc : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(bufferrr, 1024));
    }
    return (0);
}

/**
 * _myexit - exits the shell
 * @infooo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *infooo)
{
    int exitcheck;

    if (infooo->argv[1])  /* If there is an exit arguement */
    {
        exitcheck = _erratoi(infooo->argv[1]);
        if (exitcheck == -1)
        {
            infooo->status = 2;
            print_error(infooo, "Illegal number: ");
            _eputs(infooo->argv[1]);
            _eputchar('\n');
            return (1);
        }
        infooo->err_num = _erratoi(infooo->argv[1]);
        return (-2);
    }
    infooo->err_num = -1;
    return (-2);
}


