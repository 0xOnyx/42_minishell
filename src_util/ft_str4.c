#include "minishell.h"

int	ft_rmv_char(char **buffadr, int i)
{
	int		x;
	int		j;
	size_t	size;
	char	*str;
	char	*tmp;

	ft_strdup(&str, *buffadr);
	size = ft_strlen(str);
	if (ft_calloc((void **)&tmp, size, sizeof(char)))
		return (-1);
	x = 0;
	j = 0;
	while (x < size-1)
	{
		if (x == i)
		{
			j++;
		}
		tmp[x] = str[j];
		//printf("{--%s--}[%d]{%d}{%d}{%d} char : {%c}\n", str, i, size, x, j, str[j]);
		x++;
		j++;
	}
	*buffadr = tmp;
	del_malloc(str);
	return (0);
}
