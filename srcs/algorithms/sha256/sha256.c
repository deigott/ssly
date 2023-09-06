#include "ssly.h"

int     check_sha256_stdin_reading()
{
    if (!(g_ssly->args->options & OPT_SUM) && g_ssly->args->files == NULL)
        return (1);
    if (g_ssly->args->options & OPT_PRINT)
        return (1);
    return (0);
}

void print_ha256_hash(char *filename, int fd){
    if (fd == 0)
    {
        if (!(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_PRINT))
            printf("(stdin)= ");
        else if (!(g_ssly->args->options & OPT_QUIET) && g_ssly->args->options & OPT_PRINT)
            printf("(\"%s\")= ", g_ssly->sha256_ctx->string);
        else if (g_ssly->args->options & OPT_QUIET && g_ssly->args->options & OPT_PRINT)
            printf("%s\n", g_ssly->sha256_ctx->string);
    }
    else if (fd == -1  && !(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_REVER))
        printf("SHA256 (\"%s\") = ", filename);
    else if (fd != 0 && !(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_REVER))
        printf("SHA256 (%s) = ", filename);
    for (int i = 0; i < 32; i++) {
		printf("%02x", g_ssly->sha256_ctx->hash[i]);
	}
    if (!(g_ssly->args->options & OPT_QUIET) && g_ssly->args->options & OPT_REVER)
    {
        if (fd == -1)
            printf(" \"%s\"", filename);
        else if (fd != 0)
            printf(" %s", filename);
    }
    printf("\n");
    if (g_ssly->sha256_ctx->string)
    {
        free(g_ssly->sha256_ctx->string);
        g_ssly->sha256_ctx->string = NULL;
    }
}

void    store_sha256_buffer(char *buffer, size_t size)
{
    char *stringTmp;

    stringTmp = g_ssly->sha256_ctx->string;
    if (g_ssly->sha256_ctx->string == NULL)
        g_ssly->sha256_ctx->string = ft_strjoin("", buffer, size);
    else
        g_ssly->sha256_ctx->string = ft_strjoin(g_ssly->sha256_ctx->string, buffer, size);
    if (stringTmp != NULL)
    {
        free(stringTmp);
        stringTmp = NULL;
    }
    return ;
}


void  sha256_file(char *filename, int fd) {
    char *buffer;
    size_t size;

    size = 0;
    buffer = (char *)malloc(sizeof(char) * 1024);
    if (buffer == NULL)
        show_errors("ft_ssl: error can't allocate\n", EXIT_FAILURE);

    sha256_init();
    while ((size = read(fd, buffer, 1024)) > 0)
    {
        if (fd == 0)
            store_sha256_buffer(buffer, size);
        sha256_update((uchar *)buffer, size);
    }
	sha256_final();
    print_ha256_hash(filename, fd);
    free(buffer);
    buffer = NULL;
    free(g_ssly->sha256_ctx);
    g_ssly->sha256_ctx = NULL;
}

void  sha256_string(char *string)
{
    sha256_init();
    sha256_update((uchar *)g_ssly->args->string, ft_strlen(g_ssly->args->string));
    sha256_final();

	print_ha256_hash(string, -1);
    free(g_ssly->sha256_ctx);
    g_ssly->sha256_ctx = NULL;
}

void    sha256()
{
    int i;
    int fd;

    /* TO-DO: Handling input options */
    /* Reading from stdin */
    if (check_sha256_stdin_reading())
        sha256_file("", STDIN_FILENO);
    /* Reading from string */
    if (g_ssly->args->options & OPT_SUM)
        sha256_string(g_ssly->args->string);
    /* Reading from files */
    if (g_ssly->args->files)
    {
        i = 0;
        while (g_ssly->args->files[i])
        {
            fd = open(g_ssly->args->files[i], O_RDONLY);
            if (fd < 0)
                printf("ft_ssl: %s: %s: No such file or directory\n", g_ssly->args->command, g_ssly->args->files[i]);
            else
                sha256_file(g_ssly->args->files[i], fd);
            i++;
        }
    }
    return ;
}



