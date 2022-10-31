#include "minishell.h"

void	safe_exit(void)
{
	t_data	*data;

	data = get_data(NULL);
	free_all();
	exit(0);
}

int get_pwd(char **buff)
{
	if (ft_malloc((void **)buff, 255)
		||  !getcwd(*buff, 255))
		return (1);
	return (0);
}

int cd_fn(char *path)
{
	if (chdir((const char *)path) < 0)
		return (1);
	return (0);
}

int echo_cmd(t_command *command)
{
	int		option;

	option = 0;
	if (ft_strncmp(*command->arguments, "-n", 2) == 0)
	{
		command->arguments++;
		option++;
	}
	while (command->arguments)
		ft_putstr(*(command->arguments++), 1);
	if (option)
		ft_putstr("\n", 1);
	return (0);
}