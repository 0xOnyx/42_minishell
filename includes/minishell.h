#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <terminos.h>
# include <curses.h>
# include <term.h>

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


t_command *parser(char *str);

#endif