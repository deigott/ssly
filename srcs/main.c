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
    if (g_ssly->args->files) {
        printf("  files:\n");
        for (int i = 0; g_ssly->args->files[i]; i++) {
            printf("    %s\n", g_ssly->args->files[i]);
        }
    } else {
        printf("  files: NULL\n");
    }

    printf("  options: %d\n", g_ssly->args->options);

    // Check the options using the defined constants
    if (g_ssly->args->options & OPT_HELP) {
        printf("  OPT_HELP is set\n");
    }
    if (g_ssly->args->options & OPT_PRINT) {
        printf("  OPT_PRINT is set\n");
    }
    if (g_ssly->args->options & OPT_REVER) {
        printf("  OPT_REVER is set\n");
    }
    if (g_ssly->args->options & OPT_SUM) {
        printf("  OPT_SUM is set: %s\n", g_ssly->args->string);
    }
    if (g_ssly->args->options & OPT_QUIET) {
        printf("  OPT_QUIET is set\n");
    }
    return (0); 
}