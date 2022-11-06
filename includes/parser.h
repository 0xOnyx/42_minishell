#ifndef PARSER_H
# define PARSER_H

# include "includers.h"

enum	e_type
{
	IO,
	PIPE,
	WORD
};

struct s_lexical
{
	enum e_type			type;
	int					size;
	struct s_lexical	*next;
};

int			get_type(t_lexical **type, char *str, int *i);
int			create_lexical(t_lexical **lexical, enum e_type type, int size);
int			lex_add_front(t_lexical **root, enum e_type type, int size);
int			lex_add_back(t_lexical **root, enum e_type type, int size);

#endif