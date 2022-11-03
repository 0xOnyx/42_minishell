#include "minishell.h"

static void	close_dup_in(int pipe[2], int fd)
{
	if (pipe[0] != fd)
	{
		dup2(pipe[0], fd);
		close(pipe[0]);
		close(pipe[1]);
	}
}

static void	close_dup_out(int pipe[2], int fd)
{
	if (pipe[1] != fd)
	{
		dup2(pipe[1], fd);
		close(pipe[0]);
		close(pipe[1]);
	}
}

static int 	wait_process(int last_max)
{
	int		status;

	while (wait(&status) != -1)
		continue ;
	if (errno == ECHILD)
		return (WIFEXITED(status));
	return (0);
}

static int	get_path(char **path)
{
	char	**env;

	env = get_data(NULL)->env;
	while (*env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
		{
			*path = ((*env) + 5);
			return (0);
		}
		env++;
	}
	return (1);
}

static int get_cmd(char **command_path, char *cmd)
{
	int 	i;
	char	*tmp;
	char	*path;
	char	**paths;

	i = 0;
	if (get_path(&path) || ft_split(&paths, path, ':'))
	{
		del_malloc(path);
		return (1);
	}
	while (paths[i])
	{
		if (ft_strjoin(&tmp, paths[i], "/")
			|| ft_strjoin(command_path, tmp, cmd))
		{
			del_malloc(tmp);
			del_malloc(command_path);
			return (1);
		}
		del_malloc(tmp);
		if (access(*command_path, X_OK) == 0)
		{
			free_split(paths);
			return (0);
		}
		del_malloc(*command_path);
		i++;
	}
	free_split(paths);
	return (1);
}

static void	built_in(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0)
	{

	}
	else if (ft_strncmp(cmd, "echo"))
	echo et l’option -n
	◦ cd uniquement avec un chemin relatif ou absolu
	◦ pwd sans aucune option
	◦ export sans aucune option
	◦ unset sans aucune option
	◦ env sans aucune option ni argument
	◦ exit sans aucune option
}

int	exec_command(void)
{
	int 		last_status;
	int 		i;
	t_data		*data;
	t_command	*command;
	char 		*command_path;

	i = 0;
	data = get_data(NULL);
	command = data->command;
	while (command[i].command)
	{
		command[i].pid = fork();
		if (command[i].pid == 0)
		{
			close_dup_in(command[i].stdin, 0);
			close_dup_out(command[i].stdout, 1);
			close_dup_out(command[i].stderr, 2);
			if (!get_cmd(&command_path, command[i].command))
			{
				printf("value1 => %s\n", command_path);
				if (execve(command_path, command[i].arguments, data->env) == -1)
					perror("ERROR:");
				del_malloc(command_path);
			}
			built_in(command[i].command);
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
