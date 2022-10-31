#include "garbage.h"

int	ft_malloc(void **element, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (1);
	*element = new;
	add_front(root, new);
	return (0);
}

int	ft_calloc(void **element, size_t len, size_t nbr)
{
	if (ft_malloc(root, element, len * nbr))
		return (1);
	ft_memset(*element, 0, len * nbr);
	return (0);
}

int ft_realloc(void **element, size_t old_size, size_t new_size)
{
	void	*old;

	old = *element;
	if (!*root)
		return (ft_calloc(root, element, new_size, 1));
	if (ft_malloc(element, new_size)
		|| ft_memcpy(*element, old, old_size)
		|| del_malloc( element))
		return (1);
	return (0);
}