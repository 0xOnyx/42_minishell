#include "minishell.h"

int exec_command(char **argv, int argc, int tmp_fd, char **env)
{
	dup2(tmp_fd, 0);
	close(tmp_fd);
	argv[argc] = NULL;
	if (execve(argv[0], argv, env) < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int 	id;
	int 	res;
	int		fd[2];
	int		tmp_fd;

	i = 0;
	(void)argc;
	tmp_fd = dup(0);
	while (argv[i] && argv[i + 1])
	{
		argv = argv + 1;
		while (argv[i] && argv[i][0] != ';' && argv[i][0] != '|')
			i++;
	/*	if (strncmp(argv[0], "cd", 2) == 0)
		{
			if (i != 2)
				printf("error: cd: bad arguments");
			else if (chdir(argv[1]) < 0)
				perror("error");
			printf("value => %s\n", argv[1]);
		}
		else */ if (!argv[i] || argv[i][0] == ';')
		{
			id = fork();
			if (id == 0)
			{
				if (exec_command(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(tmp_fd);
				res = 0;
				while (res != -1)
					res = waitpid(id, NULL, WUNTRACED);
				tmp_fd = dup(0);
			}
		}
		else if (argv[i][0] == '|')
		{
			id = fork();
			if (id == 0)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
				exec_command(argv, i, tmp_fd, env);
			}
			else
			{
				close(tmp_fd);
				close(fd[1]);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}