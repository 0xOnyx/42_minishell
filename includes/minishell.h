#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PROMPT 255

# include "includers.h"


struct s_command
{
	char	*command;
	char	**arguments;
	int		pipe[2];
	int		tmp_fd;
};

struct s_data
{
	int			len_cmd;
	pid_t		*pid;
	t_lexical	*lexical;
	t_command	command;
	t_malloc	*garbage;
	char		**env;
	int			status;
	int			is_running;
};

void		safe_exit(void);
int			echo_cmd(t_command *command);
int			get_pwd(char **buff);
int			get_git(char **res);

int			init_env(char **env);
int			add_env(char *str);
int			del_env(char *str);
int			iter_env(int (*f)(char *, int));

int			cd_fn(t_command *command);
int			echo_cmd(t_command *command);
int			unset_cmd(t_command *command);
int			export_cmd(t_command *command);
int			print_env(void);
int			get_env(char **res, char *name);

int			minishell(void);
int			exec_command(void);
int			parser(char *str);

void		close_dup_in(int pipe[2], int fd);
void		close_dup_out(int pipe[2], int fd);
int			wait_process(void);
int			get_path(char **path);
int			get_cmd(char **command_path, char *cmd);
int			heredoc(int fd, char *end);


#endif