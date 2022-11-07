#ifndef PARSER_H
# define PARSER_H

# include "includers.h"

enum	e_type
{
	IO,
	PIPE,
	WORD,
	SQWORD,
	DQWORD
};

struct s_lexical
{
	enum e_type			type;
	int					size;
	char				*content;
	struct s_lexical	*next;
};

int			get_type(t_lexical **type, char *str);
int			create_lexical(t_lexical **lexical, enum e_type type, int size, char *content);
int			lex_add_front(t_lexical **root, enum e_type type, int size);
int			lex_add_back(t_lexical **root, enum e_type type, int size, char*content);
int			get_lexical(t_lexical **lst_head, char *str);

#endif