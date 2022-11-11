#include "minishell.h"

int	ft_rmv_char(char **buffadr, int i)
{
	int		x;
	size_t	size;
	char	*str;
	char	*tmp;

	ft_strdup(&str, *buffadr);
	printf("{--%s--}\n", *buffadr);
	size = ft_strlen(str);
	if (ft_calloc((void **)&tmp, size, sizeof(char)))
		return (-1);
	x = 0;
	while (x < size)
	{
		if (x != i)
		{
			tmp[x] = str[i];
			x++;
		}
		i++;
	}
	*buffadr = tmp;
	del_malloc(str);
	return (0);
}
