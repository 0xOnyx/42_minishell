#ifndef MINISHELL_H
# define MINISHELL_H

#include "includers.h"

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
	char	**arguments;
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
	t_type		type[11];
	t_command	*command;
	t_malloc	*garbage;
	char		**env;
};

void	safe_exit(void);
int		echo_cmd(t_command *command);
int 	get_pwd(char **buff);

int		init_env(char **env);
int		add_env(char *str);
int 	del_env(char *str);
int 	iter_env(size_t (*f)(char *, int));

int 	minishell(void);

#endif