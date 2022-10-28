#include "garbage.h"

int	ft_malloc(t_malloc **root, void **element, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (1);
	*element = new;
	add_front(root, new);
	return (0);
}

int	ft_calloc(t_malloc **root, void **element, size_t len, size_t nbr)
{
	if (ft_malloc(root, element, len * nbr))
		return (1);
	ft_memset(*element, 0, len * nbr);
	return (0);
}