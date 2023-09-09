#include "ssly.h"

int     check_whirlpool_stdin_reading()
{
    if (!(g_ssly->args->options & OPT_SUM) && g_ssly->args->files == NULL)
        return (1);
    if (g_ssly->args->options & OPT_PRINT)
        return (1);
    return (0);
}

void print_whirlpool_hash(char *filename, int fd){
    if (fd == 0)
    {
        if (!(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_PRINT))
            printf("(stdin)= ");
        else if (!(g_ssly->args->options & OPT_QUIET) && g_ssly->args->options & OPT_PRINT)
            printf("(\"%s\")= ", g_ssly->whirlpool_ctx->string);
        else if (g_ssly->args->options & OPT_QUIET && g_ssly->args->options & OPT_PRINT)
            printf("%s\n", g_ssly->whirlpool_ctx->string);
    }
    else if (fd == -1  && !(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_REVER))
        printf("WHIRLPOOL (\"%s\") = ", filename);
    else if (fd != 0 && !(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_REVER))
        printf("WHIRLPOOL (%s) = ", filename);
    for (int i = 0; i < 64; i++) {
        printf("%02hhx", g_ssly->whirlpool_ctx->result[i]);
    }
    if (!(g_ssly->args->options & OPT_QUIET) && g_ssly->args->options & OPT_REVER)
    {
        if (fd == -1)
            printf(" \"%s\"", filename);
        else if (fd != 0)
            printf(" %s", filename);
    }
    printf("\n");
    if (g_ssly->whirlpool_ctx->string)
    {
        free(g_ssly->whirlpool_ctx->string);
        g_ssly->whirlpool_ctx->string = NULL;
    }
}

void    store_whirlpool_buffer(char *buffer, size_t size)
{
    char *stringTmp;

    stringTmp = g_ssly->whirlpool_ctx->string;
    if (g_ssly->whirlpool_ctx->string == NULL)
        g_ssly->whirlpool_ctx->string = ft_strjoin("", buffer, size);
    else
        g_ssly->whirlpool_ctx->string = ft_strjoin(g_ssly->whirlpool_ctx->string, buffer, size);
    if (stringTmp != NULL)
    {
        free(stringTmp);
        stringTmp = NULL;
    }
    return ;
}

void  whirlpool_file(char *filename, int fd) {
    char *buffer;
    size_t size;

    size = 0;
    buffer = (char *)malloc(sizeof(char) * 1024);
    if (buffer == NULL)
        show_errors("ft_ssl: error can't allocate\n", EXIT_FAILURE);

    whirlpool_init();
    while ((size = read(fd, buffer, 1024)) > 0)
    {
        if (fd == 0)
            store_whirlpool_buffer(buffer, size);
        whirlpool_update((const unsigned char*)buffer, size);
    }
    whirlpool_final();
    print_whirlpool_hash(filename, fd);
    free(buffer);
    buffer = NULL;
    free(g_ssly->whirlpool_ctx);
    g_ssly->whirlpool_ctx = NULL;
}

void  whirlpool_string(char *string)
{
    whirlpool_init();
    whirlpool_update((const unsigned char*)g_ssly->args->string, ft_strlen(g_ssly->args->string));
    whirlpool_final();

    print_whirlpool_hash(string, -1);
    free(g_ssly->whirlpool_ctx);
    g_ssly->whirlpool_ctx = NULL;
}

void    whirlpool()
{
    int i;
    int fd;

    /* TO-DO: Handling input options */
    /* Reading from stdin */
    if (check_whirlpool_stdin_reading())
        whirlpool_file("", STDIN_FILENO);
    /* Reading from string */
    if (g_ssly->args->options & OPT_SUM)
        whirlpool_string(g_ssly->args->string);
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
                whirlpool_file(g_ssly->args->files[i], fd);
            i++;
        }
    }
    return ;
}
