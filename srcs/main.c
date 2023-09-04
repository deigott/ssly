#include "ssly.h"

t_ssly  *g_ssly;

/**
 * @brief Initialize Ping Structure
 * Allocates memory for the global ping structure and initializes its fields.
 * The structure holds information related to ping operations, including IP address,
 * arguments, loop control, ICMP header, and destination address.
 *
 * @param None.
 * @return None.
 */
void    init_struct()
{
	g_ssly = (t_ssly *)malloc(sizeof(t_ssly));
	if (g_ssly == NULL)
        show_errors("ssly: can't allocate memory\n", EX_OSERR);
    g_ssly->args = NULL;
	return ;
}


int     main(int argc, char **argv)
{
    if (argc < 2)
        show_errors("", EX_USAGE);
    init_struct();

    /* TO-DO : Parsing command line argument */
    parse_clo(argc, argv);
 
    /* Handling input stream */
    
    return (0); 
}