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

//TODO Write a function that associate a charset to a type
t_command	*parser(char *str)
{
	t_data		*data;
	t_command	*command;
	char		**test

	data = get_data(NULL);
	if (lexical_analyser(str))
		return (NULL);
	return (command);
}