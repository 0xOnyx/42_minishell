#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_strdup(t_data *data, char **dst, char *src)
{
	size_t len;

	len = ft_strlen(src);
	if (ft_calloc(&data->garbage, (void **)dst, len, 1)
		||	ft_memcpy((void *)src, (void *)dst, len))
		return (1);
	return (0);
}

int is_in_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int ft_strncmp(char *a, char *b, size_t n)
{
	size_t i;

	i = 0;
	while ((a[i] || b[i]) && i < n)
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}