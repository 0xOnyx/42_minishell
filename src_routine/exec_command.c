#include "minishell.h"

static int	built_in_main(t_lexical *lexical, t_command *command)
{
	char	*cmd;

	cmd = command->command;
	if (ft_strncmp(cmd, "export", 6) == 0 && lexical->next && lexical->next->type == WORD)
		return (!export_cmd(command));
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (!unset_cmd(command));
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (!cd_fn(command));
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		exit(free_all());
	return (0);
}

static int	built_in_fork(t_command *command)
{
	char	*cmd;
	char	*res;

	cmd = command->command;
	if (ft_strncmp(cmd, "echo", 3) == 0)
		return (!echo_cmd(command));
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (!print_env());
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (!export_cmd(command));
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
	{
		get_pwd(&res);
		ft_putstr_fd(res, 1);
		ft_putstr_fd("\n", 1);
		del_malloc(res);
		return (1);
	}
	return (0);
}

static int	get_len_cmd(t_lexical *current)
{
	int	res;

	res = 0;
	if (current->type != PIPE)
		res++;
	while (current)
	{
		if (current->type == PIPE)
			res++;
		current = current->next;
	}
	return (res);
}

static t_lexical	*get_last_cmd(t_lexical *current)
{
	while (current->next)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (current);
}

static int	get_name(char **res, t_lexical *node)
{
	while (node)
	{
		if (node->type == WORD)
		{
			*res = node->content;
			return (0);
		}
		if (node->type == IO)
			node = node->next;
		node = node->next;
	}
	*res = NULL;
	return (1);
}

static int	get_len_arg(t_lexical *node)
{
	int	len;

	len = 0;
	while (node)
	{
		if (node->type == WORD)
		{
			while (node && node->type == WORD)
			{
				len++;
				node = node->next;
			}
			return (len);
		}
		if (node->type == IO)
			node = node->next;
		node = node->next;
	}
	return (0);
}

static int	get_arg(char ***res, t_lexical *node)
{
	char	**arg;
	int		len;
	int		i;

	i = 0;
	len = get_len_arg(node);
	if (ft_calloc((void **)&arg, sizeof(char *), len + 1))
		return (1);
	while (node)
	{
		if (node->type == WORD)
		{
			while (node && node->type == WORD)
			{
				arg[i++] = node->content;
				node = node->next;
			}
			*res = arg;
			return (0);
		}
		if (node->type == IO)
			node = node->next;
		node = node->next;
	}
	*res = NULL;
	return (1);
}

static int	exec_this(t_command	*command, t_lexical *node,
					t_lexical *last, int tmp_fd)
{
	char		*command_path;
	t_lexical	*current;
	t_data		*data;

	current = node;
	dup2(tmp_fd, 0);
	close(tmp_fd);
	data = get_data(NULL);
	while (current != last && current)
	{
		if (current->type == IO)
		{
			if (current->content[0] == '>')
			{
				if (current->size == 1)
					tmp_fd = open(current->next->content,
							O_WRONLY | O_TRUNC | O_CREAT,
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
				else
					tmp_fd = open(current->next->content,
							O_WRONLY | O_APPEND | O_CREAT,
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
				if (tmp_fd < 0)
				{
					perror("Error");
					return (1);
				}
				close(1);
				dup2(tmp_fd, 1);
				close(tmp_fd);
			}
			else
			{
				if (current->size == 1)
				{
					tmp_fd = open(current->next->content,
							O_RDONLY);
					if (tmp_fd < 0)
						return (1);
					close(0);
					dup2(tmp_fd, 0);
					close(tmp_fd);
				}
				else
				{
					if (heredoc(0, current->next->content))
						return (1);
				}
			}
		}
		current = current->next;
	}
	if (!command->command)
		return (0);
	if (built_in_fork(command))
		return (0);
	if (get_cmd(&command_path, command->command))
		return (1);
	if (execve(command_path, command->arguments, data->env) < 0)
		return (1);
	return (0);
}

int	parse_command(t_lexical **lexical, int pid_i)
{
	t_data		*data;
	t_command	*command;
	t_lexical	*last;

	data = get_data(NULL);
	command = &(data->command);
	last = get_last_cmd(*lexical);
	get_name(&command->command, *lexical);
	get_arg(&command->arguments, *lexical);
	if (last->type == PIPE)
	{
		pipe(command->pipe);
		data->pid[pid_i] = fork();
		if (!data->pid[pid_i])
		{
			dup2(command->pipe[1], 1);
			close(command->pipe[1]);
			close(command->pipe[0]);
			exec_this(command, *lexical, last, command->tmp_fd);
			exit(1);
		}
		else
		{
			close(command->tmp_fd);
			command->tmp_fd = command->pipe[0];
			close(command->pipe[1]);
		}
	}
	else
	{
		if (!built_in_main(*lexical, command))
		{
			data->pid[pid_i] = fork();
			if (data->pid[pid_i] == -1)
				return (1);
			else if (!data->pid[pid_i])
			{
				if (exec_this(command, *lexical, last, command->tmp_fd))
				{
					if (errno)
						perror("Error");
					exit (1);
				}
				exit(0);
			}
		}
		close(command->tmp_fd);
	}
	del_malloc(command->arguments);
	*lexical = last->next;
	return (0);
}

int	exec_command(void)
{
	int			pid_i;
	t_data		*data;
	t_lexical	*lexical;

	pid_i = 0;
	data = get_data(NULL);
	data->command.tmp_fd = dup(0);
	lexical = data->lexical;
	data->len_cmd = get_len_cmd(lexical);
	if (ft_calloc((void **)&data->pid, sizeof(pid_t), data->len_cmd))
		return (1);
	data->is_running = 1;
	while (lexical)
	{
		if (parse_command(&lexical, data->pid[pid_i++]))
			break ;
	}
	data->status = wait_process();
	data->is_running = 0;
	del_malloc(data->pid);
	return (0);
}
