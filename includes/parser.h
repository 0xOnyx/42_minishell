/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:31:31 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:31:39 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "includers.h"

enum	e_type
{
	IO,
	PIPE,
	WORD,
};

struct s_lexical
{
	enum e_type			type;
	int					size;
	char				*content;
	struct s_lexical	*next;
};

int			get_type(t_lexical **type, char *str, int *i);
int			create_lexical(t_lexical **lexical,
				enum e_type type, int size, char *content);
int			lex_add_back(t_lexical **root, enum e_type type,
				int size, char*content);
int			lex_add_after(t_lexical **root,
				enum e_type type, int size, char *content);
int			get_lexical(t_lexical **lst_head, char *str);

void		in_dquote(int *i, char c, int quotes);
void		in_squote(int *i, char c, int quotes);
void		is_in_squote(int *i, char c, int quotes);
void		is_in_dquote(int *i, char c, int quotes);
int			ft_rmv_char(char **buffadr, size_t i);
int			get_next_space(char *str, char *charset);
int			parse_dquote(t_lexical *lst_head);
int			rem_quote(t_lexical *lst_head);
int			quoter(char **tmpcontent, int *quotes, int i, char c);

#endif
