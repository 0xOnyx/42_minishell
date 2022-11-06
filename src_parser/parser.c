#include "minishell.h"

int	lexical_analyser(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (1);
	while (!str)
	{
		i++;
	}
	return (0);
}

int	parser(t_data *data, char *str)
{
	(void)data;
	if (lexical_analyser(str))
		return (1);
	return (0);
}