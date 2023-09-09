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

void    handle_commands()
{
    // Array of command names
    const char* commandNames[] = {"md5","sha256","whirlpool"};

    HashFunction hashFunctions[] = {md5, sha256, whirlpool};

    for (size_t i = 0; i < sizeof(commandNames) / sizeof(commandNames[0]); i++) {
        if (strcmp(g_ssly->args->command, commandNames[i]) == 0) {
            hashFunctions[i]();
            return;
        }
    }
    return ;
}

int     main(int argc, char **argv)
{
    if (argc < 2)
        show_errors("", EX_USAGE);
    init_struct();

    /* TO-DO : Parsing command line argument */
    parse_clo(argc, argv);
 
    /* Handling commands */
    handle_commands();

    return (0); 
}