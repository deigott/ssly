#include "ssly.h"

int     check_stdin_reading()
{
    if (!(g_ssly->args->options & OPT_SUM) && g_ssly->args->files == NULL)
        return (1);
    if (g_ssly->args->options & OPT_PRINT)
        return (1);
    return (0);
}


void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

void    md5_file(int fd)
{
    uint8_t result[16];
    char *buffer;
    size_t size;

    size = 0;
    buffer = (char *)malloc(sizeof(char) * 1024);
    if (buffer == NULL)
        show_errors("ssly: error can't allocate\n", EXIT_FAILURE);
    printf("READING FROM %d\n", fd);

    md5_init();
    while ((size = read(fd, buffer, 1024)) > 0)
        md5_update((uint8_t *)buffer, size);

    md5_final();

    memcpy(&result, g_ssly->md5_ctx->digest, 16);
    print_hash(result);
    free(buffer);
    buffer = NULL;
    free(g_ssly->md5_ctx);
    g_ssly->md5_ctx = NULL;
    return ;
}


void    md5_string(char *string)
{
    uint8_t result[16];

    printf("READING from %s\n", string);
    md5_init();
    md5_update((uint8_t *) g_ssly->args->string, ft_strlen(g_ssly->args->string));
    md5_final();

    memcpy(&result, g_ssly->md5_ctx->digest, 16);
    // printf("%s\n", (char *)result);
    print_hash(result);
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
        md5_file(STDIN_FILENO);
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
                md5_file(fd);
            i++;
        }
    }
    return ;
}