#include "minishell.h"

int	get_pwd(char **buff)
{
	if (ft_malloc((void **)buff, 255)
		|| !getcwd(*buff, 255))
		return (1);
	return (0);
}

int	cd_fn(t_command *command)
{
	char *path;

	path = command->arguments[1];
	if (!*path)
		return (1);
	printf("value of path = >> %s\n", path);
	if (chdir((const char *)path) < 0)
		return (1);
	return (0);
}

int	echo_cmd(t_command *command)
{
	int		option;

	option = 0;
	command->arguments++;
	if (!*command->arguments)
		return (1);
	if (ft_strncmp(*command->arguments, "-n", 2) == 0)
	{
		command->arguments++;
		option++;
	}
	while (*command->arguments)
		ft_putstr_fd(*(command->arguments++), 1);
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	unset_cmd(t_command *command)
{
	char	**env;

	env = command->arguments;
	env++;
	while (*env)
		del_env(*(env++));
	return (0);
}

int print_env(void)
{
	char	**env;
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL);
	env = data->env;
	while (*env)
	{
		while (is_in_charset(*env[i], "="))
			i++;
		if (*env[i] != '\0')
		{
			ft_putstr_fd(*env, 1);
			ft_putstr_fd("\n", 1);
		}
		env++;
	}
	return (0);
}

int	get_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_export(void)
{
	int		i;
	int		len;
	char	**real_env;
	char	**new_env;

	real_env = get_data(NULL)->env;
	len = get_len(real_env);
	if (ft_calloc((void **)&new_env, sizeof(char *), len))
		return (1);
	ft_memcpy((void *)new_env, (void *)real_env, sizeof(char **) * len);
	quicksort(new_env, 0, len - 1);
	i = 0;
	while (i < len)
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	del_malloc(new_env);
	return (0);
}

int	export_cmd(t_command *command)
{
	char	**env;

	env = command->arguments;
	env++;
	if (!*env)
		return (print_export());
	while (*env)
		add_env(*(env++));
	return (0);
}
