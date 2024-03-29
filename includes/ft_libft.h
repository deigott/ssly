#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1
/**
 * Libft functions decalaration
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strstr(const char *big, const char *little);
void    ft_bzero(void *s, size_t n);
void    ft_putstr(char **string);
char	*ft_strdup(const char *s1);
char    *get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2, size_t size);
void	*ft_memset(void *b, int c, size_t len);

#endif