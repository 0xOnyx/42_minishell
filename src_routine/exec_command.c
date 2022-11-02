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
	t_data	*data;
	int		status;

	data = get_data(NULL);
	while (data->)

	waitpid()
}

int	exec_command(void)
{
	int 		i;
	t_data		*data;
	t_command	*command;

	i = 0;
	data = get_data(NULL);
	command = data->command;
	while (command[i].command)
	{
		printf("value -> %s\n",command[0].command);
		command[i].pid = fork();
		if (command[i].pid == 0)
		{
			printf("id fork => %d\n", command[i].pid);
			close_dup_in(command[i].stdin, 0);
			close_dup_out(command[i].stdout, 1);
			close_dup_out(command[i].stderr, 2);
			if (execve(command[i].command, command[i].arguments, data->env) == -1)
				perror("ERROR:");
			exit(1);
		}
		if (command->last && wait_process(i))
			return (1);
		printf("value of fork => %d\n", command[i]->pid);
		i++;
	}
	return (0);
}
