#include "minishell.h"


static int	built_in_main(t_command *command)
{
	char	*cmd;

	cmd = command->command;
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (!export_cmd(command));
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (!unset_cmd(command));
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (!print_env());
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

int	parse_command(t_lexical **lexical)
{
	t_command	*command;

	command = &(get_data(NULL)->command);
	if ((*lexical)->type == WORD)
	{

	}
	return (0);
}

int	exec_command(void)
{
	t_data		*data;
	t_lexical	*lexical;

	data = get_data(NULL);
	lexical = data->lexical;
	while (lexical)
		parse_command(&lexical);
	return (0);
}


//int	exec_command(void)
//{
//	int			i;
//	t_data		*data;
//	char		*command_path;
//
//	i = 0;
//	data = get_data(NULL);
//	while (command[i].command)
//	{
//		command[i].pid = -1;
//		if (!built_in_main(command))
//			command[i].pid = fork();
//		else
//			data->status = 0;
//		if (command[i].pid == 0)
//		{
//			if (built_in_fork(command + i))
//				exit(1);
//			if (!get_cmd(&command_path, command[i].command))
//			{
//				if (execve(command_path, command[i].arguments, data->env) == -1)
//					perror("ERROR:");
//				del_malloc(command_path);
//				ft_putstr_fd(NAME, 2);
//				ft_putstr_fd(": command not found:", 2);
//				ft_putstr_fd(command[i].command, 2);
//				ft_putstr_fd("\n", 2);
//			}
//			exit(1);
//		}
//		if (command[i].last)
//		{
//			data->status = wait_process();
//			if (command[i + 1].command
//				&& command[i + 1].status >= 0
//				&& command[i + 1].status != data->status)
//				return (1);
//		}
//		i++;
//	}
//	data->status = wait_process();
//	return (0);
//}
