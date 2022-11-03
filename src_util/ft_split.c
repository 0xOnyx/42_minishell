#include "minishell.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	res[j] = '\0';
	return (res);
}

static int	ft_is_separator(char c, char s)
{
	if (c == '\0' || c == s)
		return (1);
	return (0);
}

static size_t	max_len(char const *s, char c)
{
	size_t	res;
	size_t	i;
	size_t	len;

	i = 1;
	res = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (!ft_is_separator(s[i], c) && ft_is_separator(s[i + 1], c))
			res++;
		i++;
	}
	return (res);
}

static void	fill_tab(char **res, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	len;

	i = 0;
	x = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		j = 0;
		while (i <= len && ft_is_separator(s[i], c))
			i++;
		while (i + j < len && s[i + j] != '\0' && s[i + j] != c)
			j++;
		if (j > 0)
			res[x++] = ft_substr(s, (unsigned int)i, j);
		i += j;
	}
}

int	ft_split(char ***split, char *s, char c)
{
	size_t	len;
	char	**res;

	len = max_len(s, c);
	if (ft_malloc((void **)&res, sizeof(char *) * (len + 1)))
		return (1);
	fill_tab(res, s, c);
	res[len] = NULL;
	*split = res;
	return (0);
}