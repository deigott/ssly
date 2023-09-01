#include "ft_libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (*s1 == *s2 && *s1 != '\0' && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i != n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}