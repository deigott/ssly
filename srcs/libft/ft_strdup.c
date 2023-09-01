#include "ft_libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	size_t	i;
	char	*s;

	i = 0;
	size = ft_strlen(s1) + 1;
	s = (char *)malloc(sizeof(char) * size);
	if (s == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}