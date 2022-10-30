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

struct s_type
{
	char 		*charset;
	enum e_type	type;
};

struct s_command
{
	char	*command;
	char	*arguments;
	int 	stdin;
	int 	stdout;
	int 	stderr;
};

struct s_lexical
{
	enum e_type			type;
	char				*str;
	struct s_lexical	*next;
};

struct s_data
{
	t_type type[11];
	t_command *command;
	t_malloc *garbage;
	char **env;
};

int	parser(t_data *data, char *str);
int	init_env(t_data *data, char **env);
int	add_env(t_data *data, char *str);

#endif