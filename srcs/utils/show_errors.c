#include "ft_utils.h"


/** @brief Print function
 * Printing the error type and exit
 * to the Stdout
 *
 * @param errorstr
 * @param error_number
 * @return none
 */
void    show_errors(char *error_string, int error_number)
{
	collect_memory();
	// TO-DO: print the error string
	dprintf(2, "%s", error_string);
	// free(error_string);
	// error_string = NULL;
	if (error_number == EX_USAGE || error_number == EX_HELP)
		show_help();
	exit(error_number);
}