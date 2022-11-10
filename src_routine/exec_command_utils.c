#include "minishell.h"


int	wait_process(void)
{
	int		status;

	while (wait(&status) != -1)
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
	if (access(*command_path, X_OK) == 0)
	{
		ft_strdup(&tmp, cmd);
		return (tmp);
	}
	if (get_path(&path) || ft_split(&paths, path, ':'))
		return (1 + (0 * del_malloc(path)));
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
			return (!free_split(paths));
		del_malloc(*command_path);
		i++;
	}
	return (free_split(paths));
}