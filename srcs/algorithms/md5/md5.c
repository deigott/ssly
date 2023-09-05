#include "ssly.h"

int     check_stdin_reading()
{
    if (!(g_ssly->args->options & OPT_SUM) && g_ssly->args->files == NULL)
        return (1);
    if (g_ssly->args->options & OPT_PRINT)
        return (1);
    return (0);
}


void print_hash(char *filename, uint8_t *p, int fd){
    if (fd == 0)
    {
        if (!(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_PRINT))
            printf("(stdin)= ");
        else if (!(g_ssly->args->options & OPT_QUIET) && g_ssly->args->options & OPT_PRINT)
            printf("(\"%s\")= ", g_ssly->md5_ctx->string);
        else if (g_ssly->args->options & OPT_QUIET && g_ssly->args->options & OPT_PRINT)
            printf("%s\n", g_ssly->md5_ctx->string);
    }
    else if (fd == -1  && !(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_REVER))
        printf("MD5 (\"%s\") = ", filename);
    else if (fd != 0 && !(g_ssly->args->options & OPT_QUIET) && !(g_ssly->args->options & OPT_REVER))
        printf("MD5 (%s) = ", filename);
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    if (!(g_ssly->args->options & OPT_QUIET) && g_ssly->args->options & OPT_REVER)
    {
        if (fd == -1)
            printf(" \"%s\"", filename);
        else if (fd != 0)
            printf(" %s", filename);
    }
    printf("\n");
    if (g_ssly->md5_ctx->string)
    {
        free(g_ssly->md5_ctx->string);
        g_ssly->md5_ctx->string = NULL;
    }
}

void    store_buffer(char *buffer, size_t size)
{
    char *stringTmp;

    stringTmp = g_ssly->md5_ctx->string;
    if (g_ssly->md5_ctx->string == NULL)
        g_ssly->md5_ctx->string = ft_strjoin("", buffer, size);
    else
        g_ssly->md5_ctx->string = ft_strjoin(g_ssly->md5_ctx->string, buffer, size);
    if (stringTmp != NULL)
    {
        free(stringTmp);
        stringTmp = NULL;
    }
    return ;
}

void    md5_file(char *filename, int fd)
{
    uint8_t result[16];
    char *buffer;
    size_t size;

    size = 0;
    buffer = (char *)malloc(sizeof(char) * 1024);
    if (buffer == NULL)
        show_errors("ssly: error can't allocate\n", EXIT_FAILURE);

    md5_init();
    while ((size = read(fd, buffer, 1024)) > 0)
    {
        if (fd == 0)
            store_buffer(buffer, size);
        md5_update((uint8_t *)buffer, size);
    }
    
    md5_final();

    memcpy(&result, g_ssly->md5_ctx->digest, 16);
    print_hash(filename, result, fd);
    free(buffer);
    buffer = NULL;
    free(g_ssly->md5_ctx);
    g_ssly->md5_ctx = NULL;
    return ;
}


void    md5_string(char *string)
{
    uint8_t result[16];

    md5_init();
    md5_update((uint8_t *) g_ssly->args->string, ft_strlen(g_ssly->args->string));
    md5_final();

    memcpy(&result, g_ssly->md5_ctx->digest, 16);
    // printf("%s\n", (char *)result);
    print_hash(string,result, -1);
    free(g_ssly->md5_ctx);
    g_ssly->md5_ctx = NULL;
    return ;
}

void    md5()
{
    int i;
    int fd;

    /* TO-DO: Handling input options */
    /* Reading from stdin */
    if (check_stdin_reading())
        md5_file("", STDIN_FILENO);
    /* Reading from string */
    if (g_ssly->args->options & OPT_SUM)
        md5_string(g_ssly->args->string);
    /* Reading from files */
    if (g_ssly->args->files)
    {
        i = 0;
        while (g_ssly->args->files[i])
        {
            fd = open(g_ssly->args->files[i], O_RDONLY);
            if (fd < 0)
                printf("ssly: %s: %s: No such file or directory\n", g_ssly->args->command, g_ssly->args->files[i]);
            else
                md5_file(g_ssly->args->files[i], fd);
            i++;
        }
    }
    return ;
}