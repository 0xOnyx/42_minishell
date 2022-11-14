#include "minishell.h"

int	wait_process(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (errno == ECHILD)
		return (WIFEXITED(status));
	return (0);
}

int	get_path(char **path)
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

int	get_cmd(char **command_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**paths;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(command_path, cmd));
	if (get_path(&path) || ft_split(&paths, path, ':'))
		return (1 + (0 * del_malloc(path)));
	while (paths[i])
	{
		if (ft_strjoin(&tmp, paths[i], "/")
			|| ft_strjoin(command_path, tmp, cmd))
			return (1 + 0 * (del_malloc(tmp)
					+ del_malloc(command_path)));
		del_malloc(tmp);
		if (access(*command_path, X_OK) == 0)
			return (!free_split(paths));
		del_malloc(*command_path);
		i++;
	}
	return (free_split(paths));
}

static void	dup_close_in(int tube[2], int fd)
{
	dup2(tube[1], fd);
	close(tube[1]);
	close(tube[0]);
}

static void	dup_close_out(int tube[2], int fd)
{
	dup2(tube[0], fd);
	close(tube[1]);
	close(tube[0]);
}

int	heredoc(int fd, char *end)
{
	int		id;
	char	*current;
	char	*tmp;
	char	*res;
	size_t	len;
	int		tube[2];

	pipe(tube);
	id = fork();
	if (!id)
	{
		dup_close_in(tube, fd);
		current = NULL;
		res = NULL;
		len = ft_strlen(end);
		while (1)
		{
			current = readline("heredoc>");
			if (ft_strncmp(current, end, len + 1) == 0)
				break ;
			if (ft_strjoin(&tmp, current, res))
				return (1);
			del_malloc(res);
			free(current);
			res = tmp;
		}
		free(current);
		ft_putstr_fd(res, fd);
		del_malloc(res);
		exit(0);
	}
	dup_close_out(tube, fd);
	waitpid(id, NULL, 0);
	return (0);
}
