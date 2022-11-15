/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:32:58 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:33:00 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	printlex(t_lexical *lexical)
{
	while (lexical)
	{
		printf("List content : {%s}, size :{%d}\n", \
		lexical->content, lexical->size);
		lexical = lexical->next;
	}
}

int	get_lexical(t_lexical **lst_head, char *str)
{
	int		cnt;
	int		err;

	*lst_head = NULL;
	cnt = 0;
	while (*(str + cnt) == ' ')
		cnt++;
	err = get_type(&(*lst_head), str + cnt, &cnt);
	if (err)
		return (1);
	while ((size_t)cnt < ft_strlen(str))
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

int	parser(char *str)
{
	t_data		*data;
	t_lexical	*head;

	data = get_data(NULL);
	if (get_lexical(&head, str)
		|| parse_dquote(head))
		return (1);
	rem_quote(head);
	data->lexical = head;
	return (0);
}
