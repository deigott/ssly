#include "ft_utils.h"

/** @brief Help function
 * Printing the usage of ft_traceroute
 * to the Stdout
 *
 * @param void
 * @return none
 */
 void   show_usage( void )
{
     printf("usage: ssly command [flags] [file/string]\n");
     return ;
}

void    show_help()
{
    printf("Commands:\n");
    printf("md5\nsha256\n\n");
    printf("Flags:\n");
    printf("-p -q -r -s\n");
    return ;
}