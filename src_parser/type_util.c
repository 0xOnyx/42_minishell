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
		if (is_io(str) || is_pipe(str))
			return (i);
		i++;
	}
	return (0);
}

int	get_type(t_lexical *type, char *str)
{
	int	value;

	value = is_io(str);
	if (value)
	{
		type->type = IO;
		type->size = value;
		return (0);
	}
	value = is_pipe(str);
	if (!value)
	{
		type->type = PIPE;
		type->size = 1;
		return (0);
	}
	type->type = WORD;
	type->size = get_word_size(str);
	return (WORD);
}


