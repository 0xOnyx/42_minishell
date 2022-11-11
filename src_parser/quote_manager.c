#include "minishell.h"

void	in_dquote(int *i, char c)
{
	if (c == '"' && *i == 0)
		*i += 1;
	else if (c == '"' && *i == 1)
		*i -= 1;
}

void	in_squote(int *i, char c)
{
	if (c == '\'' && *i == 0)
		*i += 1;
	if (c == '\'' && *i == 1)
		*i -= 1;
}

void	is_in_dquote(int *i, char c)
{
	if (c == '"')
		*i += 1;
}

void	is_in_squote(int *i, char c)
{
	if (c == '\'')
		*i += 1;
}
