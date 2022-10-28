#include "garbage.h"

int	create_element(t_malloc **element, void *data)
{
	t_malloc	*new;

	new = malloc(sizeof(t_malloc));
	if (!new)
		return (1);
	new->next = NULL;
	new->content = data;
	*element = new;
	return (0);
}

int	add_front(t_malloc **root, t_malloc *element)
{
	t_malloc	*current;

	current = *root;
	if (!current)
	{
		*root  = element;
		return (0);
	}
	while (current->next)
		current = current->next;
	current->next = element;
	return (0);
}

int	get_id_malloc(t_malloc *root, void *element)
{
	int	i;

	i = 0;
	while (root)
	{
		if (root->content == element)
			return (i);
		root = root->next;
		i++;
	}
	return (-1);
}

t_malloc	*get_malloc(t_malloc *root, void *element)
{
	while (root)
	{
		if (root->content == element)
			return (root);
		root = root->next;
	}
	return (NULL);
}

int	free_node(t_malloc *current)
{
	free(current->content);
	free(current);
	return (0);
}

int	del_malloc(t_malloc **root, void *element)
{
	int			pos;
	t_malloc	*current;
	t_malloc	*tmp;

	pos = get_id_malloc(*root, element);
	current = *root;
	if (pos < 0)
		return (1);
	if (pos == 0)
	{
		free_node(current);
		*root = NULL;
		return (0);
	}
	while (--pos > 0)
		current = current->next;
	tmp = current->next->next;
	free_node(current->next);
	current->next = tmp;
	return (0);
}

int	free_all(t_malloc **root)
{
	t_malloc	*current;
	t_malloc	*last;

	current = *root;
	last = current;
	while (last)
	{
		last = current->next;
		free_node(current);
	}
	*root = NULL;
	return (0);
}