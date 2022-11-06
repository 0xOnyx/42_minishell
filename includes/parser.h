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

#endif