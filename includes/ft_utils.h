#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <sysexits.h>

# define EX_HELP        0

char	*concatenate_strings(const char *format, ...);
void	collect_memory();
void    show_errors(char *error_string, int error_number);
void    show_help();
 void   show_usage( void );
#endif