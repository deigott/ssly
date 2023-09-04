#ifndef SSLY_H
# define SSLY_H

# include <unistd.h>
# include <stdlib.h>

# include "ft_libft.h"
# include "ft_utils.h"
# include <sysexits.h>

# define OPT_HELP     (1 << 0)
# define OPT_PRINT	  (1 << 1)
# define OPT_REVER    (1 << 2)
# define OPT_SUM      (1 << 3)
# define OPT_QUIET    (1 << 4)
# define OPT_MD5	  (1 << 5)
# define OPT_SHA2     (1 << 6)

typedef struct  s_args
{
	char	*command;
	int		options;
}               t_args;


typedef struct  s_ssly
{
    t_args      		*args;

}               t_ssly;


/* Global Variable */
extern t_ssly   *g_ssly;


void    parse_clo(int len, char *clo_args[]);
#endif