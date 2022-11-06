#include "minishell.h"

static int	is_io(char *str)
{
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	return (0);
}

static int	is_pipe(char *str)
{
	return (!ft_strncmp(str, "|", 1));
}

static int	get_word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (i + 1);
		if (is_io(str + i) || is_pipe(str + i))
			return (i);
		i++;
	}
	return (i);
}

int	get_type(t_lexical **type, char *str, int *i)
{
	int	value;

	if (!(*str))
	{
		if (lex_add_back(type, 0, 0))
			return (1);
		return (0);
	}
	value = is_io(str);
	if (value)
	{
		if (lex_add_back(type, IO, value))
			return (1);
		return (0);
	}
	value = is_pipe(str);
	if (value)
	{
		if (lex_add_back(type, PIPE, 1))
			return (1);
		return (0);
	}
	if (lex_add_back(type, WORD, get_word_size(str)))
		return (1);
	return (0);
}


