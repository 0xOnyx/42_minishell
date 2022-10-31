#include "includers.h"

static void	exit_handler(int sign)
{
	if (sign == SIGINT)
		safe_exit();
}

int 	minishell(void)
{
	t_data *data;

	data = get_data(NULL);
	signal(SIGINT, &exit_handler);
	signal(SIGQUIT, &exit_handler);
	readline("test=> \n");
	return (0);
}
