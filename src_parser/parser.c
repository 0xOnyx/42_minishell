#include "parser.h"

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
	t_lexical	*nodes;
	int			cnt;
	int			err;

	nodes = NULL;
	*lst_head = nodes;
	cnt = 0;
	while (*(str + cnt) == ' ')
		cnt++;
	err = get_type(&nodes, str + cnt);
	if (err)
		return (1);
	printf("{%s}\n", nodes->content);
	cnt = nodes->size;
	while (nodes->size)
	{
		if (*(str + cnt) != ' ')
		{
			nodes = nodes->next;
			err = get_type(&nodes, str + cnt);
			printf("{%s}\n", nodes->content);
			if (err)
				return (1);
			cnt += nodes->size;
		}
		else
		{
			cnt++;
		}
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
	if (get_lexical(&head, str))
		return (1);
	if (lexical_analyser(str))
		return (1);
	//TODO CREATE REAL COMMAND IS ONLY FOR TEST +>
	cmd = calloc(sizeof(t_command), 2);
	cmd[0].command = "cd";
	cmd[0].arguments = calloc(sizeof(char *), 4);
	cmd[0].arguments[0] = "cd";
	cmd[0].arguments[1] = "..";
	cmd[0].arguments[2] = NULL;
	cmd[1].command = NULL;
	data->command = cmd;
	return (0);
}
