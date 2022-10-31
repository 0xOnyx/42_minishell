#include "minishell.h"

static void	exit_handler(int sign)
{
	if (sign == SIGINT)
	{
		safe_exit()
	}
}

int 	minishell(t_data *data)
{
	signal(SIGINT, &exit_handler);
	signal(SIGQUIT, NULL);
}
