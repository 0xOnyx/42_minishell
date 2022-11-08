#include "minishell.h"

static int	is_io(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (1);
	return (0);
}

static int	is_pipe(char *str)
{
	return (!ft_strncmp(str, "|", 1));
}

static int	get_word_size(char *str)
{
	int	i;
	int	is_in_squote;
	int	is_in_dquote;

	i = 0;
	is_in_squote = 0;
	is_in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_in_squote)
			is_in_squote = 1;
		else if (str[i] == '\'' && is_in_squote)
			is_in_squote = 0;
		if ((str[i] == '"') && !is_in_dquote)
			is_in_dquote = 1;
		else if (str[i] == '"' && is_in_dquote)
			is_in_dquote = 0;
		if (str[i] == ' ' && !is_in_dquote && !is_in_squote)
			return (i + 1);
		if (is_io(str + i) || is_pipe(str + i))
			return (i);
		i++;
	}
	if (is_in_squote || is_in_dquote)
		return (-1);
	return (i);
}

static int is_space(char *str)
{
	int	i;

	i = 0;
	while (!is_pipe(str) || !is_io(str))
	{
		if (str[i] == ' ' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	get_type(t_lexical **type, char *str)
{
	int	val;


	if (!(str))
	{
		if (lex_add_back(type, 0, 0, NULL))
			return (1);
		return (0);
	}
	else if (is_io(str))
	{
		if (lex_add_back(type, IO, is_io(str), ft_substr(str, 0, is_io(str))))
			return (1);
		return (0);
	}
	else if (is_pipe(str))
	{
		if (lex_add_back(type, PIPE, 1, ft_substr(str, 0, 1)))
			return (1);
		return (0);
	}
	else if (is_space(str))
	{
		val = get_word_size(str);
		if (val == -1)
			return (1);
		if (lex_add_back(type, WORD, val, ft_substr(str, 0, val)))
			return (1);
	}
	return (0);
}

