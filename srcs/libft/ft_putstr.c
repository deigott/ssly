#include "ft_libft.h"

void    ft_putstr(char **str)
{
    char *string;

    string = *str;
    while (*string)
    {
        write(1, string, 1);
        string++;
    }
    if (str)
    {
        free(*str);
        str = NULL;
    }
}