#include "ssly.h"

/** @Brief Init Args
 * Initialize args struct
 *
 * @param none
 * @return t_args*
 */
t_args  *init_args( void )
{
    t_args *args;

    args = (t_args *) malloc(sizeof(t_args) * 1);
    if (args == NULL)
        return (args);
    args->command = NULL;
    args->options = 0;
    return (args);
}

/**
 * @brief Parsing command line
 * parse command line argumments 
 * and store valid arguments in t_args struct
 */
void    parse_clo(int len, char *clo_args[])
{
    int i;
    char *p;

    p = NULL;
    i = 1;
    g_ssly->args = init_args();
    if (g_ssly->args == NULL)
        show_errors("ssly: can't allocate memory\n", EX_OSERR);
    
    (void) p;
    (void)clo_args;
    // TO-DO: Parsing only valid options and break if any invalid_option appears
    while (i < len)
    {
        continue;
    }
    return ;
}