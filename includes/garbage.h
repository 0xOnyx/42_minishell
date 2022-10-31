#ifndef GARBAGE_H
# define GARBAGE_H
# include "includers.h"

typedef struct s_malloc
{
	void			*content;
	struct s_malloc	*next;
}	t_malloc;

int 	create_element(void *data);
int 	add_front(t_malloc *element);
int 	del_malloc(void *element);
int 	free_all(void);

int		ft_malloc(void **element, size_t size);
int		ft_calloc(void **element, size_t len, size_t nbr);
int 	ft_realloc(void **element, size_t old_size, size_t new_size);

#endif
