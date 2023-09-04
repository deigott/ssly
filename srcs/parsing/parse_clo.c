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
	args->string = NULL;
	args->files = NULL;
	return (args);
}

void	reading_input_files(int index, int length, char *clo_args[])
{
	int i;
	int files_index;

	i = index;
	files_index = 0;

	if (index >= length)
		return ;
	g_ssly->args->files = (char **)malloc(sizeof(char *) * (length - index + 1));
	while (i < length)
		g_ssly->args->files[files_index++] = ft_strdup(clo_args[i++]);
	g_ssly->args->files[files_index] = NULL;
}

void	assign_command(const char *command)
{
	char *p;

	p = NULL;
	if (ft_strncmp(command, "md5", ft_strlen("md5")) == 0)
		g_ssly->args->command = ft_strdup(command);
	else if (ft_strncmp(command, "sha256", ft_strlen(command)) == 0)
	    g_ssly->args->command = ft_strdup(command);
	else if (ft_strncmp(command, "-h", 2) == 0 || ft_strncmp(command, "--help", ft_strlen(command)) == 0 || ft_strncmp(command, "help", ft_strlen(command)) == 0)
		show_errors("", EX_HELP);
	else
	{
		p = concatenate_strings("Invalid command '%s'; type \"help\" for a list.\n", command);
		show_errors(p, EXIT_FAILURE);
		free(p);
		p = NULL;
	}
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
	assign_command(clo_args[i++]);
	// TO-DO: Parsing only valid options and break if any invalid_option appears
	while (i < len)
	{
		if (ft_strncmp(clo_args[i], "-h", 2) == 0 || ft_strncmp(clo_args[i], "--help", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "help", ft_strlen(clo_args[i])) == 0)
			g_ssly->args->options |= OPT_HELP;
		if (ft_strncmp(clo_args[i], "-p", 2) == 0)
			g_ssly->args->options |= OPT_PRINT;
		else if (ft_strncmp(clo_args[i], "-s", 2) == 0)
		{
			g_ssly->args->options |= OPT_SUM;
			if (g_ssly->args->string == NULL)
				g_ssly->args->string = ft_strdup(clo_args[i + 1]);
			else
			{
				free(g_ssly->args->string);
				g_ssly->args->string = NULL;
				g_ssly->args->string = ft_strdup(clo_args[i + 1]);
			}
			i++;
		}
		else if (ft_strncmp(clo_args[i], "-r", 2) == 0)
			g_ssly->args->options |= OPT_REVER;
		else if (ft_strncmp(clo_args[i], "-q", 2) == 0)
			g_ssly->args->options |= OPT_QUIET;
		else if (clo_args[i][0] == '-')
		{
			p = concatenate_strings("%s: Unknown option or message digest: %s\n%s: Use -help for summary.\n", g_ssly->args->command, &clo_args[i][1], g_ssly->args->command);
			show_errors(p, EXIT_FAILURE);
			free(p);
			p = NULL;
		}
		else
			break;
		i++;
	}
	reading_input_files(i, len, clo_args);
	if (g_ssly->args->options & OPT_HELP)
		show_errors("", EX_HELP);
	if (!g_ssly->args->command)
		show_errors("ft_traceroute: missing host operand\n", EX_USAGE);
	return ;
}