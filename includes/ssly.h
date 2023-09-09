#ifndef SSLY_H
# define SSLY_H

# include <unistd.h>
# include <stdlib.h>

# include "ft_libft.h"
# include "ft_md5.h"
# include "ft_sha256.h"
# include "ft_whirlpool.h"
# include "ft_utils.h"
# include <sysexits.h>
# include <fcntl.h>

# define OPT_HELP     (1 << 0)
# define OPT_PRINT	  (1 << 1)
# define OPT_REVER    (1 << 2)
# define OPT_SUM      (1 << 3)
# define OPT_QUIET    (1 << 4)
# define OPT_MD5	  (1 << 5)
# define OPT_SHA2     (1 << 6)
# define OPT_WHIRL    (1 << 7)

typedef struct  s_args
{
	char	*command;
	char	**files;
	int		options;
	char	*string;
    int     flag_stdin;
}               t_args;


typedef struct  s_ssly
{
    t_args      		*args;
	t_md5_ctx			*md5_ctx;
	t_sha256_ctx		*sha256_ctx;
    t_whirlpool_ctx     *whirlpool_ctx;
}               t_ssly;


typedef void (*HashFunction)();

/* Global Variable */
extern t_ssly   *g_ssly;


void    parse_clo(int len, char *clo_args[]);


#endif