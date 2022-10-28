#include "minishell.h"

int	lexical_analyser(char *str)
{
	int			i;
	t_grammar	grammar

	i = 0;
	if (!str)
		return (1);
	while (!str)
	{
		get_next_grammar(str + i);
		i++;
	}
	return (0);
}


int	init_charset(t_type type[11])
{
	type
}
