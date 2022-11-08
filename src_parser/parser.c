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

void	printlex(t_lexical *lexical)
{
	while (lexical->content)
	{
		printf("List content : {%s}\n", lexical->content);
		lexical = lexical->next;
	}
	printf("List content : {%s}\n", lexical->content);
}

int	get_lexical(t_lexical **lst_head, char *str)
{
	int			cnt;
	int			err;

	*lst_head = NULL;
	cnt = 0;
	while (*(str + cnt) == ' ')
		cnt++;
	err = get_type(&(*lst_head), str + cnt);
	if (err)
		return (1);
	cnt = (*lst_head)->size;
	while (cnt < ft_strlen(str))
	{
		if (*(str + cnt) != ' ')
		{
			err = get_type(lst_head, str + cnt);
			if (err)
				return (1);
			cnt += (*lst_head)->size;
		}
		else
			cnt++;
	}
	err = get_type(lst_head, 0);
	if (err)
		return (1);
	return (0);
}

int	get_next_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

int	parse_dquote(t_lexical *lst_head)
{
	int			i;
	int			j;
	t_lexical	*nodes;
	t_data		*data;
	char		*tmp;

	data = get_data(NULL);
	j = 0;
	while (lst_head->content)
	{
		i = 0;
		while (lst_head->content[i])
		{
			if (lst_head->content[i] == '$')
			{
				get_env(&tmp, ft_substr(lst_head->content, i + \
				1, i - get_next_space(lst_head->content + i)));
				lst_head->content = ft_str_include(\
				lst_head->content, tmp, i, \
				get_next_space(lst_head->content + i) - i);
			}
			i++;
		}
		j++;
		lst_head = lst_head->next;
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
	printlex(head);
	//parse_dquote(head);
	//printlex(head);
	if (lexical_analyser(str))
		return (1);
	//TODO CREATE REAL COMMAND IS ONLY FOR TEST +>
	cmd = calloc(sizeof(t_command), 2);
	cmd[0].command = "export";
	cmd[0].arguments = calloc(sizeof(char *), 4);
	cmd[0].arguments[0] = NULL;
	cmd[1].command = NULL;
	data->command = cmd;
	return (0);
}
