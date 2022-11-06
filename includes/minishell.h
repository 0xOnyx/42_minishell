#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PROMPT 255

# include "includers.h"

struct s_type
{
	char 		*charset;
	enum e_type	type;
};

struct s_command
{
	char	*command;
	char	**arguments;
	int		stdin[2];
	int		stdout[2];
	int		stderr[2];
	pid_t	pid;
	int		last;
	int		status;
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

void		safe_exit(void);
int			echo_cmd(t_command *command);
int			get_pwd(char **buff);

int			init_env(char **env);
int			add_env(char *str);
int			del_env(char *str);
int			iter_env(size_t (*f)(char *, int));

int			cd_fn(t_command *command);
int			echo_cmd(t_command *command);

int			minishell(void);
int			exec_command(void);
t_command	*parser(char *str);

void		close_dup_in(int pipe[2], int fd);
void		close_dup_out(int pipe[2], int fd);
int			wait_process(int last_max);
int			get_path(char **path);
int			get_cmd(char **command_path, char *cmd);

#endif