#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len_str;

	i = 0;
	j = 0;
	len_str = ft_strlen(s);
	if (start > len_str)
		len = 0;
	else if (len >= len_str)
		len = len_str - start;
	if (ft_calloc((void **)&res, sizeof(char), len + 1))
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			res[j++] = s[i];
		i++;
	}
	return (res);
}