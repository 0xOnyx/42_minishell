#ifndef GARBAGE_H
# define GARBAGE_H
# include "includers.h"

typedef struct s_malloc
{
	void			*content;
	struct s_malloc	*next;
}	t_malloc;

int 	create_element(t_malloc **element, void *data);
int 	add_front(t_malloc **root, t_malloc *element);
int 	del_malloc(t_malloc **root, void *element);
int 	free_all(t_malloc **root);

int		ft_malloc(t_malloc **root, void **element, size_t size);
int		ft_calloc(t_malloc **root, void **element, size_t len, size_t nbr);
int 	ft_realloc(t_malloc **root, void **element, size_t old_size, size_t new_size);

#endif
