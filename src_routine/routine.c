#include "minishell.h"
#include <stdio.h>
int	main(int argc, char **argv, char **env)
{
	printf("%d %s value => %s\n", argc, argv[0], env[0]);

	//int res  = parser(argv[0]);
	return (0);
}