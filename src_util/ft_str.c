#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_strdup(char **dst, char *src)
{
	size_t	len;

	len = ft_strlen(src);

	 if (ft_calloc((void **)dst, sizeof(char), len + 1)
	 	|| ft_memcpy((void *)*dst, (void *)src, len))
		return (1);
	return (0);
}

int is_in_charset(char c, const char *charset)
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

size_t	ft_putstr_fd(char *str, int fd)
{
	size_t len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	return (write(fd, (void *)str, len));
}

size_t	ft_strlcat(char *dst, char *src, size_t max_len)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	res;
	size_t	i;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst < max_len)
		res = len_dst + len_src;
	else
		res = max_len + len_src;
	while (src[i] && len_dst < max_len - 1)
		dst[len_dst++] = src[i++];
	dst[len_dst] = 0;
	return (res);
}

int	ft_strjoin(char **buff, char *a, char *b)
{
	size_t 	i;
	size_t	len_max;

	i = 0;
	len_max = ft_strlen(a) + ft_strlen(b) + 1;
	if (ft_calloc((void **)buff, len_max, sizeof(char)))
		return (1);
	if (ft_strlcat(*buff, a, len_max) > len_max
		|| ft_strlcat(*buff, b, len_max + 1) > len_max)
		return (1);
	return (0);
}

int free_split(char **element)
{
	int i;

	i = 0;
	while (element[i])
		del_malloc(element[i++]);
	del_malloc(element);
	return (1);
}
