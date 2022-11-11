#include "parser.h"

void	printlex(t_lexical *lexical)
{
	while (lexical)
	{
		printf("List content : {%s}\n", lexical->content);
		lexical = lexical->next;
	}
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
	return (0);
}

int	get_next_space(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_in_charset(str[i], charset))
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
	int			quotes[2];

	j = 0;
	ft_bzero(quotes, 2);
	while (lst_head)
	{
		if (ft_strdup(&tmpcontent, lst_head->content))
			return (1);
		i = 0;
		while (tmpcontent[i])
		{
			in_squote(&(quotes[0]), tmpcontent[i]);
			in_dquote(&(quotes[1]), tmpcontent[i]);
			if (tmpcontent[i] == '$' && (!quotes[0] || quotes[1]))
			{
				if (!get_env(&tmp, ft_substr(tmpcontent, i + \
				1, get_next_space(tmpcontent + i + 1, " \"'$"))))
				{
					lst_head->content = ft_str_include(\
					tmpcontent, tmp, i, \
					get_next_space(tmpcontent + i + 1, " \"'$") + 1);
				}
				else
					lst_head->content = ft_str_include(tmpcontent, "", i, \
					get_next_space(tmpcontent + i + 1, " \"'$") + 1);
			}
			i++;
		}
		j++;
		lst_head = lst_head->next;
		del_malloc(tmpcontent);
	}
	return (0);
}

int	rem_quote(t_lexical *lst_head)
{
	int			i;
	int			j;
	char		*tmpcontent;
	int			quotes[2];

	j = 0;
	ft_bzero(quotes, 2);
	while (lst_head)
	{
		if (ft_strdup(&tmpcontent, lst_head->content))
			return (1);
		i = 0;
		while (tmpcontent[i])
		{
			is_in_squote(&(quotes[0]), tmpcontent[i]);
			is_in_dquote(&(quotes[1]), tmpcontent[i]);
			printf("[%c][%d][%d]\n", tmpcontent[i], quotes[1], quotes[0]);
			if ((quotes[1] && !quotes[0]) || (quotes[0] && !quotes[1]))
			{
				if (tmpcontent[i] == '"' || tmpcontent[i] == '\'')
				{
					ft_rmv_char(&tmpcontent, i);
					if (quotes[0] == 2)
						quotes[0] = 0;
					if (quotes[1] == 2)
						quotes[1] = 0;
					continue ;
				}
			}
			i++;
		}
		j++;
		del_malloc(lst_head->content);
		lst_head->content = tmpcontent;
		lst_head = lst_head->next;
	}
	return (0);
}


int	parser(char *str)
{
	t_data		*data;
	t_lexical	*head;

	data = get_data(NULL);
	if (get_lexical(&head, str)
		|| parse_dquote(head))
		return (1);
	printlex(head);
	//rem_quote(head);
	printlex(head);
	data->lexical = head;
	return (0);
}
