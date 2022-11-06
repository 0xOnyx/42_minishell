#include "minishell.h"

int	lexical_analyser(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (1);
	while (!str)
	{
		i++;
	}
	return (0);
}

int	get_lexical(t_lexical **lst_head, char *str)
{
	t_lexical	*head;
	t_lexical	*nodes;
	int			end;
	int			cnt;

	end = 0;
	nodes = NULL;
	*lst_head = nodes;
	get_type(&nodes, str, &end);
	cnt = nodes->size;
	while (nodes->size)
	{
		if (*(str + cnt) != ' ')
		{
			nodes = nodes->next;
			get_type(&nodes, str + cnt, &cnt);
			cnt += nodes->size;
		}
		else
			cnt++;
	}
	return (0);
}

//TODO: CREATE PARSING PLS !
int	parser(char *str)
{
	t_data		*data;
	t_command	*cmd;
	t_lexical	*head;

	head = NULL;
	cmd = NULL;
	data = get_data(NULL);
	get_lexical(&head, str);
	if (lexical_analyser(str))
		return (1);
	//TODO CREATE REAL COMMAND IS ONLY FOR TEST +>
//	cmd = calloc(sizeof(t_command), 2);
//	cmd[0].command = "echo";
//	cmd[0].arguments = calloc(sizeof(char *), 3);
//	cmd[0].arguments[0] = "echo";
//	cmd[0].arguments[1] = "HELLO WORLD";
//	cmd[0].arguments[2] = NULL;
//	cmd[1].command = NULL;
//	data->command = cmd;
	return (0);
}