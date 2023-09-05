# include "ft_libft.h"


char	*ft_strjoin(char const *s1, char const *s2, size_t size)
{
	int		l1;
	int		i;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	i = 0;
	p = malloc(sizeof(char *) * (l1 + size));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < (int)size)
	{
		p[i + l1] = s2[i];
		i++;
	}
    if (p[i - 1 + l1] == '\n')
        p[i - 1 + l1] = '\0';
    else
	    p[i + l1] = '\0';
	return (p);
}