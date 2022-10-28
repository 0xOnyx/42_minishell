#ifndef MINISHELL_H
# define MINISHELL_H

# include "includers.h"

enum 	e_type
{
	IO1,
	IO2,
	IO3,
	IOR,
	PIPE,
	AMPERSAND,
	OPTION,
	OPTION2,
	WORD
};

typedef struct s_type
{
	char 		*charset;
	enum e_type	type;
}	t_type;

typedef struct s_command
{
	char	*command;
	char	*options;
	char	*options2;
	char	*arguments;
	int 	stdin;
	int 	stdout;
	int 	stderr;
}	t_command;

typedef struct s_lexical
{
	enum e_type			type;
	char				*str;
	struct s_lexical	*next;
}	t_lexical;

typedef struct s_data
{
	t_type		type[11];
	t_command	*command;
	t_malloc	*garbage;
}	t_data;

int	parser(t_data *data, char *str);

#endif