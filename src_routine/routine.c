#include "minishell.h"



int	main(int argc, char **argv, char **env)
{
	t_data	data;


	(void)argv;
	(void)argc;
	data = (t_data){};
	if (init_env(&data, env))
	{
		free_all(&data.garbage);
		return (1);
	}
	minishell(&data);
	free_all(&data.garbage);
	return (0);
}