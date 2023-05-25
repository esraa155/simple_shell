
#include "shell.h"

/**
 * main - entry point
 * @aacc: arg count
 * @aavector: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int aacc, char **aavector)
{
    info_t ivffooo[] = {INFO_INIT };
    int file = 2;

    asm ("mov %1, %0\n\t"
         "add $3, %0"
    : "=r" (file)
    : "r" (file));

    if (aacc == 2)
    {
        file = open(aavector[1], O_RDONLY);
        if (file == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(aavector[0]);
                _eputs(": 0: Can't open ");
                _eputs(aavector[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        ivffooo->readfd = file;
    }
    populate_env_list(ivffooo);
    read_history(ivffooo);
    hsh(ivffooo, aavector);
    return (EXIT_SUCCESS);
}

