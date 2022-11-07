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

	data = get_data(NULL);
	env = data->env;
	while (*env++)
	{
		//TODO: FINISH THE shit
	}
	return (0);
}

//TODO: create export print function check is require to sort element
int	print_export(void)
{

	//TODO : ADD QUICKSORT
	//	quicksort();

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