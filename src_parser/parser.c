#include "parser.h"

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
	err = get_type(&(*lst_head), str, &cnt);
	if (err)
		return (1);
	while (cnt < ft_strlen(str))
	{
		if (*(str + cnt) != ' ')
		{
			err = get_type(lst_head, str + cnt, &cnt);
			if (err)
				return (1);
		}
		else
			cnt++;
	}
	err = get_type(lst_head, 0, &cnt);
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
		if (is_in_charset(str[i], " \"'$"))
			break ;
		i++;
	}
	return (i);
}

int	parse_dquote(t_lexical *lst_head)
{
	int			i;
	int			j;
	char		*tmp;
	char		*tmpcontent;
	static int	quotes[2];

	j = 0;
	while (lst_head->content)
	{
		if (ft_strdup(&tmpcontent, lst_head->content))
			return (1);
		i = 0;
		while (tmpcontent[i])
		{
			in_squote(&(quotes[0]), tmpcontent[i]);
			in_dquote(&(quotes[1]), tmpcontent[i])
			if (tmpcontent[i] == '$' && (!quotes[0] || quotes[1]))
			{
				if (!get_env(&tmp, ft_substr(tmpcontent, i + \
				1, get_next_space(tmpcontent + i + 1))))
				{
					lst_head->content = ft_str_include(\
					tmpcontent, tmp, i, \
					get_next_space(tmpcontent + i + 1) + 1);
				}
				else
					lst_head->content = ft_str_include(tmpcontent, "", i, \
					get_next_space(tmpcontent + i + 1) + 1);
			}
			i++;
		}
		j++;
		lst_head = lst_head->next;
		free(tmpcontent);
	}
	return (0);
}

int	parser(char *str)
{
	t_data		*data;
	t_lexical	*head;

	data = get_data(NULL);
	if (get_lexical(&head, str)
		|| parse_dquote(head)
		|| init_command(&cmd, head))
		return (1);
	data->lexical = head;
	return (0);
}
