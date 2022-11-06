#include "minishell.h"


static int	built_in_main(t_command *command)
{
	char	*cmd;
	char	*res;

	cmd = command->command;
	if (ft_strncmp(cmd, "export", 6) == 0)
	{
//		◦ export sans aucune option
		return (1);
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0)
	{
//		◦ unset sans aucune option
		return (1);
	}
	else if (ft_strncmp(cmd, "env", 3) == 0)
	{
//		◦ env sans aucune option ni argument
		return (1);
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
	{
		printf("cd command exce\n");
		cd_fn(command);
		return (1);
	}
	else if (ft_strncmp(cmd, "exit", 4) == 0)
	{
//	◦ exit sans aucune option
		return (1);
	}
	return (0);
}

static int	built_in_fork(t_command *command)
{
	char	*cmd;
	char	*res;

	cmd = command->command;
	if (ft_strncmp(cmd, "echo", 3) == 0)
	{
		//	echo et l’option -n
		return (1);
	}
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
	{
		printf("value of pwd => %s\n", cmd);
		get_pwd(&res);
		ft_putstr_fd(res, 1);
		free(res);
		return (1);
	}
	return (0);
}

int	exec_command(void)
{
	int			last_status;
	int			i;
	t_data		*data;
	t_command	*command;
	char		*command_path;

	i = 0;
	data = get_data(NULL);
	command = data->command;
	while (command[i].command)
	{
		command[i].pid = -1;
		if (!built_in_main(command))
			command[i].pid = fork();
		if (command[i].pid == 0)
		{
			close_dup_in(command[i].stdin, 0);
			close_dup_out(command[i].stdout, 1);
			close_dup_out(command[i].stderr, 2);
			if (!built_in_fork(command + i))
				exit(1);
			if (!get_cmd(&command_path, command[i].command))
			{
				if (execve(command_path, command[i].arguments, data->env) == -1)
					perror("ERROR:");
				del_malloc(command_path);
				ft_putstr_fd(NAME, 2);
				ft_putstr_fd(": command not found:", 2);
				ft_putstr_fd(command[i].command, 2);
				ft_putstr_fd("\n", 2);
			}
			exit(1);
		}
		if (command[i].last)
		{
			last_status = wait_process(i);
			if (command[i + 1].command
				&& command[i + 1].status >= 0
				&& command[i + 1].status != last_status)
				return (1);
		}
		i++;
	}
	return (0);
}
